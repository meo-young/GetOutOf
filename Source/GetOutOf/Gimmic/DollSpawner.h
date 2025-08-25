#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DollSpawner.generated.h"

class ULevelSequence;

UCLASS()
class GETOUTOF_API ADollSpawner : public AActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void StartSpawn();

protected:
	void SpawnDoll();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	ULevelSequence* LightOnLevelSequence;
	
	UPROPERTY(EditDefaultsOnly, Category = "변수")
	TSubclassOf<AActor> DollClass;

private:
	TArray<FTransform> SpawnLocations;
	uint8 CurrentSpawnIndex = 0;
	uint8 bIsPlayBGM : 1 = false;

};
