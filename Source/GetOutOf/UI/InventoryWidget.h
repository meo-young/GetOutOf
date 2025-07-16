#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UMultiLineEditableTextBox;
class UButton;
class USlotWidget;
class UVerticalBox;
class UImage;
class UTextBlock;

USTRUCT()
struct FSlots
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<USlotWidget*> Slots;
};

UCLASS()
class GETOUTOF_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	/** Slot을 해제하는 함수 */
	void UnLockSlot(uint8 EmotionIndex, uint8 SlotIndex);
	
	/** Inventory 내용을 업데이트하는 함수 */
	UFUNCTION(BlueprintCallable)
	void UpdateInventory(const FString& Title, const FString& Dialogue, UTexture2D* Image);

private:
	/** 박스의 자식 SlotWidget들을 SlotWidgets 배열에 추가 */
	void AddSlotWidgetsFromBox(UVerticalBox* Box, uint8 EmotionType = 0);

	/** "D" 키를 눌러서 다음 감정으로 이동 */
	void NavigateToNextEmotion();

	/** "A" 키를 눌러서 이전 감정으로 이동 */
	void NavigateToPreviousEmotion();

	/** 현재 감정 박스의 인덱스를 저장 */
	void SetVisibleEmotionBox(int32 EmotionIndex);

	/** 모든 감정 박스를 숨김 */
	void HideAllEmotionBoxes();

	/** "S" 키를 눌러서 다음 슬롯으로 이동 */
	void NavigateToNextSlot();

	/** "W" 키를 눌러서 이전 슬롯으로 이동 */
	void NavigateToPreviousSlot();

	/** 현재 선택된 슬롯의 인덱스를 업데이트 */
	void UpdateSlotSelection();

	/** 현재 감정의 슬롯 개수를 반환 */
	int32 GetCurrentEmotionSlotCount() const;

	/** 버튼의 투명도를 조절하는 함수 */
	void SetButtonOpacity(UButton* Button, float Opacity);

	/** 감정 버튼들을 업데이트하는 함수 */
	void UpdateEmotionButtons();

	/** 현재 슬롯에 따라 인벤토리의 UI를 업데이트하는 함수 */
	void UpdateCurrentSlotUI();

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TitleText;

	UPROPERTY(meta = (BindWidget))
	UMultiLineEditableTextBox* DialogueText;

	UPROPERTY(meta = (BindWidget))
	UImage* DialogueImage;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* HappinessBox;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* DenialBox;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* AngerBox;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* BargainingBox;

	UPROPERTY(meta = (BindWidget))
	UButton* HappinessButton;

	UPROPERTY(meta = (BindWidget))
	UButton* DenialButton;

	UPROPERTY(meta = (BindWidget))
	UButton* AngerButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BargainingButton;

	/** 감정 박스들을 저장하는 배열 */
	UPROPERTY()
	TArray<FSlots> EmotionTypes;

	/** 현재 활성화된 감정 박스 인덱스 (0: Happiness, 1: Denial, 2: Anger, 3: Bargaining) */
	UPROPERTY()
	int32 CurrentEmotionIndex;

	/** 현재 활성화된 슬롯 인덱스 */
	UPROPERTY()
	int32 CurrentSlotIndex;
	
};
