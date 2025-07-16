#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StageSubSystem.generated.h"

struct FLevelSequenceDataTable;
class AGOOLevelSequenceActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStageStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStageEnded);

UCLASS(Blueprintable)
class GETOUTOF_API UStageSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

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

private:
	/** 현재 스테이지의 EndLevelSequence를 호출하는 함수 */
	void ShowEndLevelSequence();

protected:
	/** 스테이지별 LevelSequence 데이터 테이블 */
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
	UDataTable* LevelSequenceDataTable;

	/** 스테이지별 LevelSequence 정보 */
	TArray<FLevelSequenceDataTable*> LevelSequenceRows;

private:
	/** 현재 스테이지 번호를 나타내는 변수 */
	uint8 CurrentStageNum = 0;

	/** 현재 StartLevelSequence에 대한 캐싱 데이터 */
	UPROPERTY()
	AGOOLevelSequenceActor* CurrentStartLSA;

	/** 현재 EndLevelSequence에 대한 캐싱 데이터 */
	UPROPERTY()
	AGOOLevelSequenceActor* CurrentEndLSA;
	
};
