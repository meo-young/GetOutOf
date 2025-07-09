#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

class UTextBlock;

UCLASS()
class GETOUTOF_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ActivateTimerText();
	
	UFUNCTION()
	void ResetTimerText();

private:
	void UpdateTimerText();

private:
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* TimerText;

	FTimerHandle TimerHandle;

	uint8 Hours = 0;
	uint8 Minutes = 0;
	uint8 Seconds = 0;
	
};
