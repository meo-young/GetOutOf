#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProloguePlayerController.generated.h"

class UDialogueWidget;

UCLASS()
class GETOUTOF_API AProloguePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* InPawn) override;

protected:
	/** Dialogue 위젯 클래스 */
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UDialogueWidget> DialogueWidgetClass;

	/** Dialogue 위젯 인스턴스 */
	UPROPERTY()
	UDialogueWidget* DialogueWidgetInstance;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UDialogueWidget* GetDialogueWidget() const { return DialogueWidgetInstance; }
	
};
