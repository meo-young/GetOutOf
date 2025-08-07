#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactable.h"
#include "InteractableItem.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventStart);

UCLASS()
class GETOUTOF_API AInteractableItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	AInteractableItem();
	virtual void BeginPlay() override;

public:
	/** LevelSequence에 Interact가 시작될 때 호출되는 델리게이트 */
	UPROPERTY(BlueprintAssignable)
	FOnInteractionStart OnInteractionStartDelegate;

	/** 이벤트 조건이 만족될 때 호출되는 델리게이트 */
	UPROPERTY(BlueprintAssignable)
	FOnEventStart OnEventStartDelegate;
	
	/** Interactable 인터페이스의 Interact 함수 구현 */
	virtual void Interact_Implementation() override;

private:
	UFUNCTION()
	void DisableCollision();

	UFUNCTION()
	void DestroyItem();
	
protected:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true), Category ="Inventory")
	uint8 EmotionType = 0;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true), Category ="Inventory")
	uint8 SlotIndex = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	UBoxComponent* EventTriggerBox = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	USceneComponent* SceneComponent = nullptr;
};