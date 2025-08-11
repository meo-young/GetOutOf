#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MannequinSpawner.generated.h"

class ULevelSequence;
class ACrawlCharacter;
class AStealthCharacter;

UCLASS()
class GETOUTOF_API AMannequinSpawner : public AActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void StartSpawn();

protected:
	UFUNCTION()
	void OnStageEnded();
	
	void SpawnMannequin();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn")
	uint8 TargetSpawnNum = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<ACrawlCharacter> CrawlMannequinClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn")
	ULevelSequence* LightOnLevelSequence;
	
private:
	FTimerHandle SpawnTimer;
	TArray<FVector> SpawnLocations;
	TArray<uint8> SpawnOrders;
	uint8 CurrentSpawnNum = 0;
	uint8 SpawnInterval = 7;

};
