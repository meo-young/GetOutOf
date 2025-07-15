#pragma once

#include "CoreMinimal.h"
#include "Define/DefineClass.h"
#include "Sound/SoundCue.h"
#include "BGMDataTable.generated.h"

USTRUCT(BlueprintType)
struct FBGMDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	EBGM BGMType;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> SoundCue;
	
};
