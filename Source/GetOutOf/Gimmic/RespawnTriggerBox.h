#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "RespawnTriggerBox.generated.h"

UCLASS()
class GETOUTOF_API ARespawnTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
							bool bFromSweep, const FHitResult& SweepResult);
	
};
