#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EndStageTriggerBox.generated.h"

UCLASS()
class GETOUTOF_API AEndStageTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();

public:
	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
							bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OpenNextLevel();

	UFUNCTION()
	void EndStage();

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FString NextLevelName;

	FTimerHandle OpenNextLevelTimerHandle;
	FTimerHandle EndStageTimerHandle;
	
};
