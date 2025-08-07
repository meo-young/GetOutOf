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

public:
	/** 튜토리얼을 시작하는 함수 */
	UFUNCTION(BlueprintCallable)
	void StartTutorial();

	/** 플레이어를 리스폰하는 함수 */
	UFUNCTION(BlueprintCallable)
	void ReStart();

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	uint8 bIsFirstPlayTime : 1 = false;
	
};
