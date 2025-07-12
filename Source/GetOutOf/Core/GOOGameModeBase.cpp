#include "Core/GOOGameModeBase.h"
#include "EngineUtils.h"
#include "GetOutOf.h"
#include "Tutorial/TutorialManager.h"

void AGOOGameModeBase::StartPlay()
{
	Super::StartPlay();

	LOG(Warning, TEXT("게임 모드가 시작되었습니다."));
	for (ATutorialManager* TutorialManager : TActorRange<ATutorialManager>(GetWorld()))
	{
		if (IsValid(TutorialManager))
		{
			TutorialManager->StartTutorial();
		}
	}
}
