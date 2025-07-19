#include "LevelSequence/EndLevelSequenceActor.h"
#include "SubSystem/StageSubSystem.h"

void AEndLevelSequenceActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>())
	{
		StageSubsystem->OnStageEndedDelegate.AddDynamic(this, &ThisClass::StopLevelSequence);
	}
}

