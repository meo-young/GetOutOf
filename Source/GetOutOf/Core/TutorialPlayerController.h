#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TutorialPlayerController.generated.h"

class UHorrorWidget;
class UInputMappingContext;

UCLASS()
class GETOUTOF_API ATutorialPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* MappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHorrorWidget> HorrorWidgetClass = nullptr;

	UPROPERTY()
	UHorrorWidget* HorrorWidgetInstance = nullptr;
	
};
