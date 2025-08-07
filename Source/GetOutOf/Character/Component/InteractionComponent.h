#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class IInteractable;
DECLARE_MULTICAST_DELEGATE(FOnInteractionPossible);
DECLARE_MULTICAST_DELEGATE(FOnInteractionImPossible);
DECLARE_MULTICAST_DELEGATE(FOnInteractionStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionEnded);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GETOUTOF_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** 상호작용이 가능한 상태일 때 호출되는 델리게이트 */
	FOnInteractionPossible OnInteractionPossibleDelegate;

	/** 상호작용이 불가능한 상태일 때 호출되는 델리게이트 */
	FOnInteractionImPossible OnInteractionImpossibleDelegate;

	/** 마우스를 클릭해서 상호작용이 시작될 때 호출되는 델리게이트 */
	FOnInteractionStarted OnInteractionStartedDelegate;

	/** 상호작용으로 카메라 플래시 효과가 끝났을 때 호출되는 델리게이트 */
	UPROPERTY(BlueprintAssignable)
	FOnInteractionEnded OnInteractionEndedDelegate;

public:
	/** 마우스 클릭 시 호출되는 상호작용 시작 로직 함수 */
	void StartInteraction();

	/** E 클릭 시 호출되는 상호작용 시작 로직 함수 */
	void DoorInteraction();

	/** 상호작용 시작 로직 함수가 불린 후 1.5초 후 호출되는 상호작용 종료 로직 함수  */
	void EndInteraction();

private:
	FHitResult InteractionHitResult;
	FHitResult DoorHitResult;
	FCollisionQueryParams QueryParams;
	FTimerHandle CameraTimerHandle;
	
	uint8 bIsInteracting : 1 = false;

	IInteractable* InteractableObject = nullptr;

public:
	FORCEINLINE bool IsInteracting() const { return bIsInteracting; }
	
};
