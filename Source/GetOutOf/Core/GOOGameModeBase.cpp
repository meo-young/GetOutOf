#include "Core/GOOGameModeBase.h"
#include "EngineUtils.h"
#include "GetOutOf.h"
#include "Character/GOOCharacter.h"
#include "SubSystem/StageSubSystem.h"
#include "Tutorial/TutorialManager.h"

void AGOOGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>();
	StageSubsystem->StartStage();
	
}
