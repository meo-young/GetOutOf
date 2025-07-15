#include "SubSystem/StageSubSystem.h"
#include "GetOutOf.h"
#include "SoundSubSystem.h"
#include "Character/Component/PostProcessEffectComponent.h"
#include "Define/DefineClass.h"
#include "GameFramework/Character.h"

UStageSubSystem::UStageSubSystem()
{
	ConstructorHelpers::FObjectFinder<UDataTable> DT_LevelSequenceDataTable(TEXT("/Game/_GetOutOf/DataTable/DT_LevelSequence"));
	if (DT_LevelSequenceDataTable.Succeeded())
	{
		LevelSequenceDataTable = DT_LevelSequenceDataTable.Object;
	}
}

void UStageSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

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

	if (LevelSequenceRows.IsValidIndex(CurrentStageNum))
	{
		CurrentStartLSA = GetWorld()->SpawnActor<AGOOLevelSequenceActor>(LevelSequenceRows[CurrentStageNum]->StartLevelSequenceActor);
		CurrentStartLSA->PlayLevelSequenceForLoop();
	}
}

void UStageSubSystem::EndStage()
{
	if (OnStageEndedDelegate.IsBound())
	{
		LOG(Log, TEXT("스테이지 종료"));
		OnStageEndedDelegate.Broadcast();
	}

	if (IsValid(CurrentStartLSA))
	{
		CurrentEndLSA->StopLevelSequence();
	}

	++CurrentStageNum;
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
