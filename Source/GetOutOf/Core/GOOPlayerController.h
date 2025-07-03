#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GOOPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class GETOUTOF_API AGOOPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* MappingContext = nullptr;
	
};
