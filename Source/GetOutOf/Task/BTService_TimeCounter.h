#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_TimeCounter.generated.h"

struct BTServiceTimeCounterMemory
{
	float AccumulatedTime = 0.0f;
	uint8 bIsActivated : 1 = false;
};

UCLASS()
class GETOUTOF_API UBTService_TimeCounter : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_TimeCounter();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual uint16 GetInstanceMemorySize() const override { return sizeof(BTServiceTimeCounterMemory); };
	
};
