#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TutorialGameMode.generated.h"

UCLASS()
class GETOUTOF_API ATutorialGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** 튜토리얼을 시작하는 함수 */
	UFUNCTION(BlueprintCallable)
	void StartTutorial();
	
};
