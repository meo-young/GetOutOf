#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StealthAIController.generated.h"

UCLASS()
class GETOUTOF_API AStealthAIController : public AAIController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ActivateBehaviorTree();

	UFUNCTION(BlueprintCallable)
	void DeactivateBehaviorTree();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
};
