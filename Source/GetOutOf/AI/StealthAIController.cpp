#include "AI/StealthAIController.h"
#include "GetOutOf.h"

void AStealthAIController::ActivateBehaviorTree()
{
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void AStealthAIController::DeactivateBehaviorTree()
{
	StopMovement();
	UnPossess();
}
