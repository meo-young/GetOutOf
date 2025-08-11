#include "AI/StealthAIController.h"
#include "GetOutOf.h"

void AStealthAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		LOG2(TEXT("Run"));
		RunBehaviorTree(BehaviorTree);
	}
}

void AStealthAIController::ActivateBehaviorTree()
{
	if (BehaviorTree)
	{
		LOG2(TEXT("Run"));
		RunBehaviorTree(BehaviorTree);
	}
}

void AStealthAIController::DeactivateBehaviorTree()
{
	StopMovement();
	UnPossess();
}
