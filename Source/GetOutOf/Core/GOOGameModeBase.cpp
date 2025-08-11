#include "Core/GOOGameModeBase.h"
#include "EngineUtils.h"
#include "GetOutOf.h"
#include "Character/GOOCharacter.h"
#include "SubSystem/StageSubSystem.h"
#include "Tutorial/TutorialManager.h"

void AGOOGameModeBase::StartPlay()
{
	Super::StartPlay();

	/*const FString& UEDMapName = GetWorld()->GetMapName();
	const FString& CleanMapName = UEDMapName.Mid(GetWorld()->StreamingLevelsPrefix.Len());

	if (CleanMapName != "LV_LoadingTutorial")
	{
		UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>();
		StageSubsystem->StartStage();
	}*/
	
}

void AGOOGameModeBase::StartTutorial()
{
	for (ATutorialManager* TutorialManager : TActorRange<ATutorialManager>(GetWorld()))
	{
		if (IsValid(TutorialManager))
		{
			LOG2(TEXT("튜토리얼을 시작합니다"));
				
			AGOOCharacter* Player = Cast<AGOOCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
			Player->SetEnableMove(false);
			Player->SetEnableSprint(false);
			Player->SetEnableInteract(false);
			
			TutorialManager->StartTutorial();
		}
	}	
}

void AGOOGameModeBase::ReStart()
{
	// 플레이어 캐릭터를 삭제합니다.
	GetWorld()->GetFirstPlayerController()->GetPawn()->Destroy();

	// 플레이어 컨트롤러를 재시작합니다.
	RestartPlayer(GetWorld()->GetFirstPlayerController());
}
