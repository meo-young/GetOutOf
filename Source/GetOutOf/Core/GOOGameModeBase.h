#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GOOGameModeBase.generated.h"

UCLASS()
class GETOUTOF_API AGOOGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	uint8 bIsFirstPlayTime : 1 = false;
	
};
