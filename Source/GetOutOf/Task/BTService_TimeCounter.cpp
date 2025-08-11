#include "Task/BTService_TimeCounter.h"
#include "GetOutOf.h"
#include "AI/CrawlCharacter.h"
#include "AI/StealthAIController.h"

UBTService_TimeCounter::UBTService_TimeCounter()
{
	NodeName = TEXT("Timer Counter");
	bCreateNodeInstance = false;
}

void UBTService_TimeCounter::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	BTServiceTimeCounterMemory* Memory = (BTServiceTimeCounterMemory*)NodeMemory;
	Memory->AccumulatedTime += DeltaSeconds;

	if (Memory->AccumulatedTime  > 2.0f && !Memory->bIsActivated)
	{
		ACrawlCharacter* CrawlCharacter = Cast<ACrawlCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
		CrawlCharacter->ShowFadeTransition();
		Memory->bIsActivated = true;
	}
}
