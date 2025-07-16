#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HorrorWidget.generated.h"

UCLASS()
class GETOUTOF_API UHorrorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void ShowWASDTutorialWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveWASDTutorialWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowSprintTutorialWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveSprintTutorialWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowPictureTutorialWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void RemovePictureTutorialWidget();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ShowInventoryTutorialWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveInventoryTutorialWidget();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ShowFlashTutorialWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveFlashTutorialWidget();
	
};
