#include "UI/SlotWidget.h"
#include "GetOutOf.h"
#include "Styling/SlateColor.h"
#include "Styling/SlateBrush.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USlotWidget::SetOpacity(float Opacity)
{
	if (IsValid(SlotButton))
	{
		FButtonStyle NewStyle = SlotButton->GetStyle();
		FLinearColor TintColor = NewStyle.Normal.TintColor.GetSpecifiedColor();
		TintColor.A = Opacity;
		NewStyle.Normal.TintColor = FSlateColor(TintColor);

		SlotButton->SetStyle(NewStyle);
	}
}

void USlotWidget::SetTitleText(const FString& NewTitle)
{
	if (IsValid(TitleText))
	{
		TitleText->SetText(FText::FromString(NewTitle));
	}
}
