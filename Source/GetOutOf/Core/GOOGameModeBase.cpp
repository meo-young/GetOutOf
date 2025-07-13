#include "Core/GOOGameModeBase.h"
#include "EngineUtils.h"
#include "GetOutOf.h"
#include "Character/GOOCharacter.h"
#include "SubSystem/StageSubSystem.h"
#include "Tutorial/TutorialManager.h"

void AGOOGameModeBase::StartPlay()
{
	Super::StartPlay();

	bIsFirstPlayTime = false;
	
	if (bIsFirstPlayTime)
	{
		for (ATutorialManager* TutorialManager : TActorRange<ATutorialManager>(GetWorld()))
		{
			if (IsValid(TutorialManager))
			{
				LOG(Warning, TEXT("튜토리얼을 시작합니다"));
				
				AGOOCharacter* Player = Cast<AGOOCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
				Player->SetEnableMove(false);
				Player->SetEnableSprint(false);
				Player->SetEnableInteract(false);
				
				TutorialManager->StartTutorial();
			}
		}	
	}
	else
	{
		//@TODO : 스테이지 시작
		LOG(Warning, TEXT("스테이지를 시작합니다"));
		
		UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>();
		StageSubsystem->StartStage();
	}

	
}
