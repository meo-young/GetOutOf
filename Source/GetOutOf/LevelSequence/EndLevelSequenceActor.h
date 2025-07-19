#pragma once

#include "CoreMinimal.h"
#include "LevelSequence/GOOLevelSequenceActor.h"
#include "EndLevelSequenceActor.generated.h"

UCLASS()
class GETOUTOF_API AEndLevelSequenceActor : public AGOOLevelSequenceActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
};
