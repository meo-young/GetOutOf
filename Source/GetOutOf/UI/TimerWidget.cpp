#include "UI/TimerWidget.h"

#include "GetOutOf.h"
#include "Components/TextBlock.h"
#include "SubSystem/StageSubSystem.h"

void UTimerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UStageSubSystem* StageSubSystem = GetGameInstance()->GetSubsystem<UStageSubSystem>();
	if (!IsValid(StageSubSystem)) return;

	LOG(Log, TEXT("TimerWidget 델리게이트 바인딩 성공"));
	StageSubSystem->OnStageStartedDelegate.AddUObject(this, &ThisClass::ActivateTimerText);
	StageSubSystem->OnStageEndedDelegate.AddUObject(this, &ThisClass::ResetTimerText);
}

void UTimerWidget::ActivateTimerText()
{
	// 이미 활성화되어 있으면 중복 방지
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
	{
		return;
	}

	// 1초마다 UpdateTimerText 호출
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&UTimerWidget::UpdateTimerText,
		1.0f,
		true
	);
}

void UTimerWidget::ResetTimerText()
{
	// 타이머 핸들 초기화
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
    
    // 시간 값 초기화
	Hours = 0;
	Minutes = 0;
	Seconds = 0;
    
    // 텍스트 초기화
	if (TimerText)
	{
		TimerText->SetText(FText::FromString(TEXT("00:00:00")));
	}
}

void UTimerWidget::UpdateTimerText()
{
	// 1초 증가
	Seconds++;

	// 초가 60이면 분으로 넘어감
	if (Seconds >= 60)
	{
		Seconds = 0;
		Minutes++;

		// 분이 60이면 시간으로 넘어감
		if (Minutes >= 60)
		{
			Minutes = 0;
			Hours++;
		}
	}

	// 문자열 포맷: 00:00:00
	const FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d"), Hours, Minutes, Seconds);

	// UTextBlock에 표시
	if (TimerText)
	{
		TimerText->SetText(FText::FromString(TimeString));
	}
}
