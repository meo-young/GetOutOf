#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

class UTextBlock;

UCLASS()
class GETOUTOF_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

public:
	void SetDialogueText(const FString& InDialogueText);

private:
	void RemoveDialogueText();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DialogueText;

	FTimerHandle DialogueTextTimer;
	
};
