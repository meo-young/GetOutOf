#include "Gimmic/EndStageTriggerBox.h"
#include "Components/ShapeComponent.h"
#include "SubSystem/StageSubSystem.h"

void AEndStageTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActorBeginOverlap);
	GetCollisionComponent()->SetGenerateOverlapEvents(true);
}

void AEndStageTriggerBox::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>();
		StageSubsystem->EndStage();
	}
}
