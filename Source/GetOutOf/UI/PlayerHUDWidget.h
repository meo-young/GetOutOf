#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

class UInventoryWidget;
class UHorrorWidget;
class UTimerWidget;
class UCrossHairWidget;

UCLASS()
class GETOUTOF_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UCrossHairWidget* CrossHairWidget;

	UPROPERTY(meta = (BindWidget))
	UTimerWidget* TimerWidget;

	UPROPERTY(meta = (BindWidget))
	UHorrorWidget* HorrorWidget;

public:
	FORCEINLINE UCrossHairWidget* GetCrossHairWidget() const { return CrossHairWidget; }
	FORCEINLINE UTimerWidget* GetTimerWidget() const { return TimerWidget; }
	FORCEINLINE UHorrorWidget* GetHorrorWidget() const { return HorrorWidget; }
	
};
