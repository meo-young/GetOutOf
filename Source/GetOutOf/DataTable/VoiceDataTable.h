#pragma once

#include "CoreMinimal.h"
#include "Define/DefineClass.h"
#include "Sound/SoundCue.h"
#include "VoiceDataTable.generated.h"

USTRUCT(BlueprintType)
struct FVoiceDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	EVoiceType VoiceType;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> Voice;

	UPROPERTY(EditDefaultsOnly, meta = (MultiLine = true))
	FText DialogueText;

};