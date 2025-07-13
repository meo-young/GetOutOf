#pragma once

#include "CoreMinimal.h"
#include "LevelSequence/GOOLevelSequenceActor.h"
#include "LevelSequenceDataTable.generated.h"

USTRUCT(BlueprintType)
struct FLevelSequenceDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGOOLevelSequenceActor> StartLevelSequenceActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGOOLevelSequenceActor> EndLevelSequenceActor;
	
};
