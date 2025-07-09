#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrossHairWidget.generated.h"

class UImage;

UCLASS()
class GETOUTOF_API UCrossHairWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetCrossHairImageToRed();

	UFUNCTION()
	void SetCrossHairImageToWhite();

private:
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UImage* CrossHairImage;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* WhiteCrossHairTexture;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* RedCrossHairTexture;
	
};
