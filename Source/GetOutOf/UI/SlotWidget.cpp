#include "UI/SlotWidget.h"
#include "Components/TextBlock.h"

void USlotWidget::SetTitleText(const FString& Title)
{
	if (IsValid(TitleText))
	{
		TitleText->SetText(FText::FromString(Title));
	}
}
