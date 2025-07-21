#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "RespawnTriggerBox.generated.h"

class AGOOLevelSequenceActor;
class ULevelSequence;
class AGOOCharacter;

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


private:
	void RespawnPlayer(AGOOCharacter* Player);
	void EndStage();

private:
	UPROPERTY(EditInstanceOnly, meta =(AllowPrivateAccess = "true"))
	TObjectPtr<AGOOLevelSequenceActor> FadeInLevelSequenceActor;

	UPROPERTY(EditInstanceOnly, meta =(AllowPrivateAccess = "true"))
	TObjectPtr<AGOOLevelSequenceActor> FadeOutLevelSequenceActor;

	FTimerHandle TriggerBoxTimerHandle;
	FTimerHandle RespawnTimerHandle;

};
