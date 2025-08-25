#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RedGreenLightManager.generated.h"

UCLASS()
class GETOUTOF_API ARedGreenLightManager : public AActor
{
	GENERATED_BODY()

public:
	ARedGreenLightManager();
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void StartRedGreenLight();

protected:
	void UpdateRedGreenLight();
	void HandleRedLight();
	void HandleGreenLight();
	void InvokeRedGreenLightUpdateRandomly();

private:
	FTimerHandle RedGreenLightTimer;
	uint8 bIsGameStarted : 1 = false;
	uint8 bIsRedLight : 1 = true;
	FRotator PreviousControlRotation = FRotator::ZeroRotator;

};
