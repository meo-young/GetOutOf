#include "UI/DialogueWidget.h"
#include "Components/TextBlock.h"

void UDialogueWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (DialogueText)
	{
		DialogueText->SetText(FText::GetEmpty());
	}
}

void UDialogueWidget::SetDialogueText(const FString& InDialogueText)
{
	if (DialogueText)
	{
		DialogueText->SetText(FText::FromString(InDialogueText));

		uint8 DialogueLength = InDialogueText.Len();

		GetWorld()->GetTimerManager().SetTimer(DialogueTextTimer, this, &ThisClass::RemoveDialogueText, DialogueLength/5, false);
	}
}

void UDialogueWidget::RemoveDialogueText()
{
	if (DialogueText)
	{
		DialogueText->SetText(FText::GetEmpty());
	}
}
