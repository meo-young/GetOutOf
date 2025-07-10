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
	virtual void NativeOnInitialized() override;

public:
	/** 1초마다 UpdateTimerText를 호출하여 타이머를 업데이트 */
	UFUNCTION()
	void ActivateTimerText();

	/** 타이머를 초기화하고 텍스트를 "00:00:00"으로 설정 */
	UFUNCTION()
	void ResetTimerText();

private:
	/** 타이머를 업데이트하여 텍스트를 갱신 */
	void UpdateTimerText();

private:
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* TimerText;

	FTimerHandle TimerHandle;

	uint8 Hours = 0;
	uint8 Minutes = 0;
	uint8 Seconds = 0;
	
};
