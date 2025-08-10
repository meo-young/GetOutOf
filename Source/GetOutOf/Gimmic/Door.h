#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactable.h"
#include "Door.generated.h"

class UBoxComponent;

UCLASS()
class GETOUTOF_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ADoor();
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void UnLockDoor();

	UFUNCTION()
	void LockDoor();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayDoorOpenAnimation();

	virtual void Interact_Implementation() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* GlassMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Components")
	FName NextStageName;

private:
	FTimerHandle StartStageTimer;
	FTimerHandle EndStageTimer;
	FTimerHandle RestartTimer;

};
