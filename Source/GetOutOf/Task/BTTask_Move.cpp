#include "Task/BTTask_Move.h"
#include "AI/StealthAIController.h"
#include "AI/StealthCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Move::UBTTask_Move()
{
	NodeName = TEXT("Move");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Move::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AStealthAIController* AIController = Cast<AStealthAIController>(OwnerComp.GetAIOwner());
	AStealthCharacter* StealthCharacter = Cast<AStealthCharacter>(OwnerComp.GetAIOwner()->GetCharacter());

	if (!AIController || !StealthCharacter) return EBTNodeResult::Failed;
	
	AIController->MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn());
	StealthCharacter->ResumeAnimation();
	
	return EBTNodeResult::InProgress;
}

void UBTTask_Move::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AStealthAIController* AIController = Cast<AStealthAIController>(OwnerComp.GetAIOwner());
	AStealthCharacter* StealthCharacter = Cast<AStealthCharacter>(OwnerComp.GetAIOwner()->GetCharacter());

	if (!AIController || !StealthCharacter) return;

	if (!StealthCharacter->IsOutOfPlayerSight() && !StealthCharacter->IsObstacleBetweenPlayer())
	{
		AIController->GetBlackboardComponent()->SetValueAsBool("IsMoving", false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
