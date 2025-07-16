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
			
			TutorialManager->PictureTutorial.TutorialStartDelegate.AddUObject(this, &ThisClass::ShowPictureTutorialWidget);
			TutorialManager->PictureTutorial.TutorialEndDelegate.AddUObject(this, &ThisClass::RemovePictureTutorialWidget);

			TutorialManager->InventoryTutorial.TutorialStartDelegate.AddUObject(this, &ThisClass::ShowInventoryTutorialWidget);
			TutorialManager->InventoryTutorial.TutorialEndDelegate.AddUObject(this, &ThisClass::RemoveInventoryTutorialWidget);

			TutorialManager->FlashTutorial.TutorialStartDelegate.AddUObject(this, &ThisClass::ShowFlashTutorialWidget);
			TutorialManager->FlashTutorial.TutorialEndDelegate.AddUObject(this, &ThisClass::RemoveFlashTutorialWidget);
		}
	}
}
