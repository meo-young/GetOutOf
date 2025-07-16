#pragma once

#include "CoreMinimal.h"
#include "DialogueDataTable.generated.h"

class UTexture2D;
class FText;

USTRUCT(BlueprintType)
struct FDialogueDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FString TitleText;

	UPROPERTY(EditDefaultsOnly, meta = (MultiLine = true))
	FText DialogueText;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* DialogueImage;
	
};