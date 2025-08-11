#include "Task/BTTask_Idle.h"
#include "GetOutOf.h"
#include "AI/StealthAIController.h"
#include "AI/StealthCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Idle::UBTTask_Idle()
{
	NodeName = TEXT("Idle");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AStealthAIController* AIController = Cast<AStealthAIController>(OwnerComp.GetAIOwner());
	AStealthCharacter* StealthCharacter = Cast<AStealthCharacter>(OwnerComp.GetAIOwner()->GetCharacter());

	if (!AIController || !StealthCharacter) return EBTNodeResult::Failed;

	AIController->StopMovement();
	StealthCharacter->StopAnimation();
	
	return EBTNodeResult::InProgress;
}

void UBTTask_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	AStealthAIController* AIController = Cast<AStealthAIController>(OwnerComp.GetAIOwner());
	AStealthCharacter* StealthCharacter = Cast<AStealthCharacter>(OwnerComp.GetAIOwner()->GetCharacter());

	if (!AIController || !StealthCharacter) return;

	if (!StealthCharacter->GetIsActivated()) return;

	if (!StealthCharacter->CheckAllConditions())
	{
		AIController->GetBlackboardComponent()->SetValueAsBool("IsMoving", true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
