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
	void ShowPictreTutorialWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void RemovePictreTutorialWidget();
	
};
