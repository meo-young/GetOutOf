#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInteractionStarted);
DECLARE_MULTICAST_DELEGATE(FOnInteractionEnded);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GETOUTOF_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FOnInteractionStarted OnInteractionStartedDelegate;
	FOnInteractionEnded OnInteractionEndedDelegate;

private:
	void BindToInteractionStartDelegate();
	void BindToInteractionEndedDelegate();

private:
	FHitResult InteractionHitResult;
	FCollisionQueryParams QueryParams;

	uint8 bIsInteracting : 1 = false;
		
};
