#include "UI/HorrorWidget.h"
#include "EngineUtils.h"
#include "GetOutOf.h"
#include "Tutorial/TutorialManager.h"

void UHorrorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	for (ATutorialManager* TutorialManager : TActorRange<ATutorialManager>(GetWorld()))
	{
		if (IsValid(TutorialManager))
		{
			TutorialManager->WASDTutorial.TutorialStartDelegate.AddUObject(this, &ThisClass::ShowWASDTutorialWidget);
			TutorialManager->WASDTutorial.TutorialEndDelegate.AddUObject(this, &ThisClass::RemoveWASDTutorialWidget);

			TutorialManager->SprintTutorial.TutorialStartDelegate.AddUObject(this, &ThisClass::ShowSprintTutorialWidget);
			TutorialManager->SprintTutorial.TutorialEndDelegate.AddUObject(this, &ThisClass::RemoveSprintTutorialWidget);
			
			TutorialManager->PictureTutorial.TutorialStartDelegate.AddUObject(this, &ThisClass::ShowPictreTutorialWidget);
			TutorialManager->PictureTutorial.TutorialEndDelegate.AddUObject(this, &ThisClass::RemovePictreTutorialWidget);
		}
	}
}
