#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RedGreenLightManager.generated.h"

class AInteractableItem;

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

	UFUNCTION(BlueprintCallable)
	void FinishGame();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ShowJumpScare();
	
	void UpdateRedGreenLight();
	void HandleRedLight();
	void HandleGreenLight();
	void InvokeRedGreenLightUpdateRandomly();
	void SpawnDollItem();
	void DestroyDollItem();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	TSubclassOf<AInteractableItem> DollItemClass;

	UPROPERTY()
	TObjectPtr<AInteractableItem> DollItemInstance = nullptr;

private:
	FTimerHandle ActivateRedLightTimer;
	FTimerHandle RedGreenLightTimer;
	uint8 bIsGameStarted : 1 = false;
	uint8 bIsRedLight : 1 = false;
	FRotator PreviousControlRotation = FRotator::ZeroRotator;

};
