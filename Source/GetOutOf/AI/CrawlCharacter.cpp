#include "AI/CrawlCharacter.h"
#include "GetOutOf.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Character/GOOCharacter.h"
#include "SubSystem/StageSubSystem.h"

void ACrawlCharacter::BeginPlay()
{
	Super::BeginPlay();

	UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>();
	StageSubsystem->OnStageEndedDelegate.AddDynamic(this, &ThisClass::DestroyAI);
}

bool ACrawlCharacter::CheckAllConditions()
{
	const bool SuperCondition = Super::CheckAllConditions();

	return IsPlayerFlashLightOn() && IsAcceptanceDistance() && SuperCondition;
}

bool ACrawlCharacter::IsPlayerFlashLightOn()
{
	const AGOOCharacter* Player = Cast<AGOOCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	return Player->IsPlayerFlashLightOn();
}

bool ACrawlCharacter::IsAcceptanceDistance()
{
	// 플레이어에 대한 참조를 받아옵니다.
	const APawn* Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	// 플레이어와 AI의 거리를 계산합니다.
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector CurrentLocation = GetActorLocation();
	const float Distance = FVector::Dist2D(PlayerLocation, CurrentLocation);

	// 계산 결과를 리턴합니다.
	return Distance <= AcceptanceDistance;
}

void ACrawlCharacter::ShowFadeTransition()
{
	ALevelSequenceActor* OutActor;
	ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeTransitionLevelSequence, FMovieSceneSequencePlaybackSettings(), OutActor)->Play();

	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ThisClass::DestroyAI, 0.6f, false);
}

void ACrawlCharacter::DestroyAI()
{
	if (IsValid(this))
	{
		Destroy();
	}
}
