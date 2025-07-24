#include "Core/TutorialGameMode.h"
#include "EngineUtils.h"
#include "GetOutOf.h"
#include "Character/GOOCharacter.h"
#include "Tutorial/TutorialManager.h"

void ATutorialGameMode::StartTutorial()
{
	LOG(Warning, TEXT("StartPlay() 호출됨"));

	for (ATutorialManager* TutorialManager : TActorRange<ATutorialManager>(GetWorld()))
	{
		if (IsValid(TutorialManager))
		{
			LOG(Warning, TEXT("튜토리얼을 시작합니다"));
				
			AGOOCharacter* Player = Cast<AGOOCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
			Player->SetEnableMove(false);
			Player->SetEnableSprint(false);
			Player->SetEnableInteract(false);
			//Player->SetEnableFlashLight(false);
			//Player->SetEnableInventory(false);
				
			TutorialManager->StartTutorial();
		}
	}	
}
