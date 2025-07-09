#pragma once

#include "CoreMinimal.h"
#include "Define/DefineClass.h"
#include "Sound/SoundCue.h"
#include "SFXDataTable.generated.h"

USTRUCT(BlueprintType)
struct FSFXDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	ESFX SFXType;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> SoundCue;
};
