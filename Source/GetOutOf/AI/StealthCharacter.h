#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Item/InteractableItem.h"
#include "StealthCharacter.generated.h"

class UCameraComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStealthInteractionStart);


UCLASS()
class GETOUTOF_API AStealthCharacter : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	AStealthCharacter();
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnInteractionStart OnInteractionStartDelegate;

public:
	/** 플레이어의 시야각 밖에 AI가 존재하는 지 확인하는 함수입니다. */
	bool IsOutOfPlayerSight();

	/** 플레이어와 AI 사이에 장애물이 존재하는 지 확인하는 함수입니다. */
	bool IsObstacleBetweenPlayer();

	/** AI의 애니메이션을 잠시 정지하는 함수입니다. */
	UFUNCTION(BlueprintCallable)
	void StopAnimation();

	/** AI의 애니메이션을 재개하는 함수입니다. */
	UFUNCTION(BlueprintCallable)
	void ResumeAnimation();

	virtual void Interact_Implementation() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowDeadScene();

protected:
	UFUNCTION()
	void DisableCollision();
	
	UFUNCTION()
	void DestroyItem();

	UFUNCTION()
	void OnPlayerOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> EventTriggerBox = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;

private:
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	
};
