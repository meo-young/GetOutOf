#include "SubSystem/StageSubSystem.h"
#include "GetOutOf.h"
#include "DataTable/LevelSequenceDataTable.h"
#include "LevelSequence/GOOLevelSequenceActor.h"

void UStageSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LevelSequenceDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/_GetOutOf/DataTable/DT_LevelSequence.DT_LevelSequence"));

	if (IsValid(LevelSequenceDataTable))
	{
		LevelSequenceDataTable->GetAllRows<FLevelSequenceDataTable>(TEXT(""), LevelSequenceRows);
	}
	else
	{
		LOG(Error, TEXT("LevelSequenceDataTable이 유효하지 않습니다"));
	}
}

void UStageSubSystem::StartStage()
{
	if (OnStageStartedDelegate.IsBound())
	{
		LOG(Log, TEXT("스테이지 시작"));
		OnStageStartedDelegate.Broadcast();
	}

	LOG(Warning, TEXT("%d StageNum : %d"), CurrentStageNum, LevelSequenceRows.Num());

	if (LevelSequenceRows.IsValidIndex(CurrentStageNum))
	{
		LOG(Warning, TEXT("현재 스테이지 번호: %d"), CurrentStageNum);
		CurrentStartLSA = GetWorld()->SpawnActor<AGOOLevelSequenceActor>(LevelSequenceRows[CurrentStageNum]->StartLevelSequenceActor);
		CurrentStartLSA->PlayLevelSequenceForLoop();
	}

	++CurrentStageNum;
}

void UStageSubSystem::EndStage()
{
	if (OnStageEndedDelegate.IsBound())
	{
		LOG(Log, TEXT("스테이지 종료"));
		OnStageEndedDelegate.Broadcast();
	}
}

void UStageSubSystem::ShowEndLevelSequence()
{
	if (IsValid(CurrentStartLSA))
	{
		CurrentStartLSA->StopLevelSequence();
	}
	
	if (LevelSequenceRows.IsValidIndex(CurrentStageNum))
	{
		CurrentEndLSA = GetWorld()->SpawnActor<AGOOLevelSequenceActor>(LevelSequenceRows[CurrentStageNum]->EndLevelSequenceActor);
		CurrentEndLSA->PlayLevelSequence();
	}
}
