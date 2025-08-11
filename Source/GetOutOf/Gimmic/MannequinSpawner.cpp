#include "Gimmic/MannequinSpawner.h"
#include "GetOutOf.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "AI/CrawlCharacter.h"
#include "AI/StealthCharacter.h"
#include "Character/GOOCharacter.h"
#include "SubSystem/SoundSubSystem.h"
#include "SubSystem/StageSubSystem.h"

void AMannequinSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocations.Empty();
	SpawnLocations.Emplace(FVector(5100.0f, 5449.0f, 105.0f));
	SpawnLocations.Emplace(FVector(6113.0f, 4613.0f, 112.0f));
	SpawnLocations.Emplace(FVector(6715.0f, 5533.0f, 100.0f));

	SpawnOrders.Empty();
	const uint8 RandNum = FMath::RandRange(0, 2);

	if (RandNum == 0)
	{
		SpawnOrders.Append({0, 2, 0, 1, 2, 1, 0});
	}
	else if (RandNum == 1)
	{
		SpawnOrders.Append({2, 0, 2, 1, 0, 1, 0});
	}
	else if (RandNum == 2)
	{
		SpawnOrders.Append({1, 0, 2, 0, 1, 2, 0});
	}
	else
	{
		SpawnOrders.Append({2, 0, 1, 2, 0, 1, 2});
	}
	
}

void AMannequinSpawner::StartSpawn()
{
	// OnStageEnded에 바인딩이 안 된 경우에만 바인딩
	UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>();
	if (!StageSubsystem->OnStageEndedDelegate.Contains(this, FName("OnStageEnd")))
	{
		LOG2(TEXT("바인딩 안 된 상태라 바인딩 시작"));
		StageSubsystem->OnStageEndedDelegate.AddDynamic(this, &ThisClass::OnStageEnded);	
	}
	
	CurrentSpawnNum = 0;
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ThisClass::SpawnMannequin, SpawnInterval, true, 0.0f);
}

void AMannequinSpawner::SpawnMannequin()
{
	if (CurrentSpawnNum == TargetSpawnNum)
	{
		LOG2(TEXT("타겟 스폰 수에 도달함. 타이머 클리어 시작"));
		GetWorldTimerManager().ClearTimer(SpawnTimer);

		ALevelSequenceActor* OutActor;
		ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LightOnLevelSequence, FMovieSceneSequencePlaybackSettings(), OutActor)->Play();

		UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>();
		StageSubsystem->ClearStage();

		USoundSubSystem* SoundSubSystem = GetGameInstance()->GetSubsystem<USoundSubSystem>();
		SoundSubSystem->StopBGM();

		AGOOCharacter* Player = Cast<AGOOCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		Player->SetEnableMove(true);
		
	}
	else
	{
		ACrawlCharacter* CrawlMannequin = GetWorld()->SpawnActor<ACrawlCharacter>(CrawlMannequinClass, SpawnLocations[SpawnOrders[CurrentSpawnNum]], FRotator::ZeroRotator);
		CrawlMannequin->SetActivated(true);

		++CurrentSpawnNum;
	}
}

void AMannequinSpawner::OnStageEnded()
{
	LOG2(TEXT("타이머 클리어"));
	GetWorldTimerManager().ClearTimer(SpawnTimer);

	UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>();
	StageSubsystem->OnStageEndedDelegate.RemoveDynamic(this, &ThisClass::OnStageEnded);
}
