#include "UI/InventoryWidget.h"
#include "GetOutOf.h"
#include "SlotWidget.h"
#include "Character/GOOCharacter.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "SubSystem/DialogueSubsystem.h"

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// EmotionTypes를 4개 감정 타입으로 초기화 (각각 6개 슬롯)
	EmotionTypes.Empty();
	EmotionTypes.SetNum(4);

	// 헬퍼 함수로 각 박스 처리
	AddSlotWidgetsFromBox(HappinessBox, 0);
	AddSlotWidgetsFromBox(DenialBox, 1);
	AddSlotWidgetsFromBox(AngerBox, 2);
	AddSlotWidgetsFromBox(BargainingBox, 3);
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 초기 상태: HappinessBox만 Visible
	CurrentEmotionIndex = 0;
	SetVisibleEmotionBox(CurrentEmotionIndex);
	UpdateSlotSelection();
	UpdateEmotionButtons();
	UpdateCurrentSlotUI();
    
	// 포커스 설정 (키 입력을 받기 위해)
	SetIsFocusable(true);
	SetKeyboardFocus();
}

void UInventoryWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply UInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	const FKey Key = InKeyEvent.GetKey();

	if (InKeyEvent.GetKey() == EKeys::Tab)
	{
		// 안전하게 지연 제거!
		GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			AGOOCharacter* Player = Cast<AGOOCharacter>(GetOwningPlayer()->GetCharacter());
			Player->RemoveInventoryWidget();

			RemoveFromParent();
		});

		return FReply::Handled();
	}
	else if (Key == EKeys::D)
	{
		NavigateToNextEmotion();
		UpdateCurrentSlotUI();
		return FReply::Handled();
	}
	else if (Key == EKeys::A)
	{
		NavigateToPreviousEmotion();
		UpdateCurrentSlotUI();
		return FReply::Handled();
	}
	else if (Key == EKeys::S)
	{
		NavigateToNextSlot();
		UpdateCurrentSlotUI();
		return FReply::Handled();
	}
	else if (Key == EKeys::W)
	{
		NavigateToPreviousSlot();
		UpdateCurrentSlotUI();
		return FReply::Handled();
	}
    
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UInventoryWidget::UnLockSlot(uint8 EmotionIndex, uint8 SlotIndex)
{
	if (EmotionTypes.IsValidIndex(EmotionIndex) && EmotionTypes[EmotionIndex].Slots.IsValidIndex(SlotIndex))
	{
		if (USlotWidget* SlotWidget = EmotionTypes[EmotionIndex].Slots[SlotIndex])
		{
			if (FDialogueDataTable* DialogueData = GetGameInstance()->GetSubsystem<UDialogueSubsystem>()->GetDialogueByID(EmotionIndex, SlotIndex))
			{
				SlotWidget->SetTitleText(DialogueData->TitleText);
				SlotWidget->SetDialogueData(DialogueData);
			}
		}
	}
}

void UInventoryWidget::UpdateInventory(const FString& Title, const FString& Dialogue, UTexture2D* Image)
{
	if (IsValid(TitleText))
	{
		TitleText->SetText(FText::FromString(Title));
	}

	if (IsValid(DialogueText))
	{
		DialogueText->SetText(FText::FromString(Dialogue));
	}

	if (IsValid(DialogueImage) && Image)
	{
		DialogueImage->SetBrushFromTexture(Image);
	}
	
}

void UInventoryWidget::AddSlotWidgetsFromBox(UVerticalBox* Box, uint8 EmotionType)
{
	if (!Box) return;
    
	for (int32 i = 0; i < Box->GetChildrenCount(); ++i)
	{
		if (USlotWidget* SlotWidget = Cast<USlotWidget>(Box->GetChildAt(i)))
		{
			LOG(Log, TEXT("SlotWidget %s is added to SlotWidgets array."), *SlotWidget->GetName());
			EmotionTypes[EmotionType].Slots.Emplace(SlotWidget);
		}
	}
}

void UInventoryWidget::NavigateToNextEmotion()
{
	// D키: 다음 감정으로 이동 (최대 3까지, 그 이후는 변화 없음)
	if (CurrentEmotionIndex < 3)
	{
		USlotWidget* PreviousSlot = EmotionTypes[CurrentEmotionIndex].Slots[CurrentSlotIndex];
		PreviousSlot->SetOpacity(0.0f);
		
		CurrentEmotionIndex++;
		
		// 감정이 바뀌면 슬롯 인덱스를 0으로 리셋하되, 유효한 범위 내에서만
		CurrentSlotIndex = 0;
        
		SetVisibleEmotionBox(CurrentEmotionIndex);
		UpdateSlotSelection();
		UpdateEmotionButtons();
	}
}

void UInventoryWidget::NavigateToPreviousEmotion()
{
	// A키: 이전 감정으로 이동 (최소 0까지, 그 이전은 변화 없음)
	if (CurrentEmotionIndex > 0)
	{
		USlotWidget* PreviousSlot = EmotionTypes[CurrentEmotionIndex].Slots[CurrentSlotIndex];
		PreviousSlot->SetOpacity(0.0f);
		
		CurrentEmotionIndex--;

		// 감정이 바뀌면 슬롯 인덱스를 0으로 리셋하되, 유효한 범위 내에서만
		CurrentSlotIndex = 0;
        
		SetVisibleEmotionBox(CurrentEmotionIndex);
		UpdateSlotSelection();
		UpdateEmotionButtons();
	}
}

void UInventoryWidget::SetVisibleEmotionBox(int32 EmotionIndex)
{
	// 모든 박스를 숨김
	HideAllEmotionBoxes();
    
	// 지정된 감정 박스만 표시
	switch (EmotionIndex)
	{
	case 0: // Happiness
		if (HappinessBox)
		{
			HappinessBox->SetVisibility(ESlateVisibility::Visible);
		}
		break;
            
	case 1: // Denial
		if (DenialBox)
		{
			DenialBox->SetVisibility(ESlateVisibility::Visible);
		}
		break;
            
	case 2: // Anger
		if (AngerBox)
		{
			AngerBox->SetVisibility(ESlateVisibility::Visible);
		}
		break;
            
	case 3: // Bargaining
		if (BargainingBox)
		{
			BargainingBox->SetVisibility(ESlateVisibility::Visible);
		}
		break;
            
	default:
		LOG(Warning, TEXT("Invalid emotion index: %d"), EmotionIndex);
		break;
	}
}

void UInventoryWidget::HideAllEmotionBoxes()
{
	if (HappinessBox)
	{
		HappinessBox->SetVisibility(ESlateVisibility::Hidden);
	}
    
	if (DenialBox)
	{
		DenialBox->SetVisibility(ESlateVisibility::Hidden);
	}
    
	if (AngerBox)
	{
		AngerBox->SetVisibility(ESlateVisibility::Hidden);
	}
    
	if (BargainingBox)
	{
		BargainingBox->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInventoryWidget::NavigateToNextSlot()
{
	// S키: 다음 슬롯으로 이동 (현재 감정의 슬롯 개수에 따라 순환)
	int32 SlotCount = GetCurrentEmotionSlotCount();
	if (SlotCount > 0)
	{
		USlotWidget* PreviousSlot = EmotionTypes[CurrentEmotionIndex].Slots[CurrentSlotIndex];
		PreviousSlot->SetOpacity(0.0f);
		
		CurrentSlotIndex = (CurrentSlotIndex + 1) % SlotCount;
		UpdateSlotSelection();
	}
}

void UInventoryWidget::NavigateToPreviousSlot()
{
	// W키: 이전 슬롯으로 이동 (현재 감정의 슬롯 개수에 따라 순환)
	int32 SlotCount = GetCurrentEmotionSlotCount();
	if (SlotCount > 0)
	{
		USlotWidget* PreviousSlot = EmotionTypes[CurrentEmotionIndex].Slots[CurrentSlotIndex];
		PreviousSlot->SetOpacity(0.0f);
		
		CurrentSlotIndex = (CurrentSlotIndex - 1 + SlotCount) % SlotCount;
		UpdateSlotSelection();
	}
}

void UInventoryWidget::UpdateSlotSelection()
{
	// 현재 선택된 슬롯에 대한 시각적 피드백이나 로직 처리
	int32 SlotCount = GetCurrentEmotionSlotCount();
    
	if (SlotCount > 0 && CurrentSlotIndex < SlotCount && CurrentSlotIndex >= 0)
	{
		USlotWidget* CurrentSlot = EmotionTypes[CurrentEmotionIndex].Slots[CurrentSlotIndex];
		if (CurrentSlot)
		{
			CurrentSlot->SetOpacity(0.15f);
		}
	}
}

int32 UInventoryWidget::GetCurrentEmotionSlotCount() const
{
	if (EmotionTypes.IsValidIndex(CurrentEmotionIndex))
	{
		return EmotionTypes[CurrentEmotionIndex].Slots.Num();
	}
	return 0;
}

void UInventoryWidget::SetButtonOpacity(UButton* Button, float Opacity)
{
	if (IsValid(Button))
	{
		FButtonStyle NewStyle = Button->GetStyle();
		FLinearColor TintColor = NewStyle.Normal.TintColor.GetSpecifiedColor();
		TintColor.A = Opacity;
		NewStyle.Normal.TintColor = FSlateColor(TintColor);

		Button->SetStyle(NewStyle);
	}
}

void UInventoryWidget::UpdateEmotionButtons()
{
	// 먼저 모든 버튼을 0으로 초기화
	SetButtonOpacity(HappinessButton, 0.0f);
	SetButtonOpacity(DenialButton, 0.0f);
	SetButtonOpacity(AngerButton, 0.0f);
	SetButtonOpacity(BargainingButton, 0.0f);

	// 현재 선택된 EmotionIndex에 맞는 버튼만 0.15로 설정
	switch (CurrentEmotionIndex)
	{
	case 0:
		SetButtonOpacity(HappinessButton, 0.15f);
		break;
	case 1:
		SetButtonOpacity(DenialButton, 0.15f);
		break;
	case 2:
		SetButtonOpacity(AngerButton, 0.15f);
		break;
	case 3:
		SetButtonOpacity(BargainingButton, 0.15f);
		break;
	default:
		break;
	}
}

void UInventoryWidget::UpdateCurrentSlotUI()
{
	if (FDialogueDataTable* DialogueData = EmotionTypes[CurrentEmotionIndex].Slots[CurrentSlotIndex]->GetDialogueData())
	{
		UpdateInventory(DialogueData->TitleText, DialogueData->DialogueText.ToString(), DialogueData->DialogueImage);
	}
	else
	{
		UpdateInventory(TEXT("???"), TEXT("???"), nullptr);
	}
}
