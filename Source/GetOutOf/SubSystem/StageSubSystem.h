#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StageSubSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStageStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStageEnded);

UCLASS()
class GETOUTOF_API UStageSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** 스테이지 시작 시 호출되는 델리게이트 */
	UPROPERTY(BlueprintAssignable)
	FOnStageStarted OnStageStartedDelegate;

	/** 스테이지 종료 시 호출되는 델리게이트 */
	UPROPERTY(BlueprintAssignable)
	FOnStageEnded OnStageEndedDelegate;

public:
	/** 스테이지 시작 함수 */
	void StartStage();

	/** 스테이지 종료 함수 */
	void EndStage();
	
};
