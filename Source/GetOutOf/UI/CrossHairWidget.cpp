#include "UI/CrossHairWidget.h"
#include "GetOutOf.h"
#include "Components/Image.h"

void UCrossHairWidget::SetCrossHairImageToRed()
{
	if (IsValid(CrossHairImage) && IsValid(RedCrossHairTexture))
	{
		CrossHairImage->SetBrushFromTexture(RedCrossHairTexture);	
	}
}

void UCrossHairWidget::SetCrossHairImageToWhite()
{
	if (IsValid(CrossHairImage) && IsValid(WhiteCrossHairTexture))
	{
		CrossHairImage->SetBrushFromTexture(WhiteCrossHairTexture);	
	}
}
