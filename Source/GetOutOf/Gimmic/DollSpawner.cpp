#include "DollSpawner.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Define/DefineClass.h"
#include "SubSystem/SoundSubSystem.h"
#include "Subsystem/StageSubSystem.h"

void ADollSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocations.Empty();
	SpawnLocations.Emplace(FRotator(0.f, 65.f, 0.f),FVector(6997.0f, 5360.0f, 68.0f));
	SpawnLocations.Emplace(FRotator(0.f, 90.f, 0.f),FVector(6149.0f, 4609.0f, 75.0f));
	SpawnLocations.Emplace(FRotator(0.f, 180.f, 0.f),FVector(9264.0f, 5419.0f, 68.0f));
}

void ADollSpawner::StartSpawn()
{
	FTimerHandle SpawnTimer;
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ThisClass::SpawnDoll, 3.0f, false);
}

void ADollSpawner::SpawnDoll()
{
	USoundSubSystem* SoundSubSystem = GetGameInstance()->GetSubsystem<USoundSubSystem>();

	if (!bIsPlayBGM)
	{
		SoundSubSystem->PlayBGM(EBGM::LightHorrorBGM);
		bIsPlayBGM = true;
	}

	// 3번 이상 스폰 시도 시 스테이지 종료
	if (CurrentSpawnIndex >= 3)
	{
		UStageSubSystem* StageSubSystem = GetGameInstance()->GetSubsystem<UStageSubSystem>();
		StageSubSystem->ClearStage();

		SoundSubSystem->StopBGM();
		
		ALevelSequenceActor* OutActor;
		ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LightOnLevelSequence, FMovieSceneSequencePlaybackSettings(), OutActor)->Play();
		return;
	}

	// 인형 소환 후 보이스 재생
	const AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(DollClass, SpawnLocations[CurrentSpawnIndex].GetLocation(), SpawnLocations[CurrentSpawnIndex].GetRotation().Rotator());
	SoundSubSystem->PlayVoiceSFX(EVoiceType::FindMe, SpawnedActor->GetActorLocation());

	// Spawn 카운트 증가
	++CurrentSpawnIndex;
}
