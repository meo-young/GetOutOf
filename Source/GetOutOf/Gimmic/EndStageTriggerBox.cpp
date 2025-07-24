#include "Gimmic/EndStageTriggerBox.h"

#include "Character/GOOCharacter.h"
#include "Components/ShapeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystem/StageSubSystem.h"

void AEndStageTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActorBeginOverlap);
}

void AEndStageTriggerBox::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (AGOOCharacter* Player = Cast<AGOOCharacter>(OtherActor))
		{
			GetWorldTimerManager().SetTimer(EndStageTimerHandle, this, &ThisClass::EndStage, 1.0f, false);
			GetWorldTimerManager().SetTimer(OpenNextLevelTimerHandle, this, &ThisClass::OpenNextLevel, 4.0f, false);
		}
	}
}

void AEndStageTriggerBox::OpenNextLevel()
{
	if (!NextLevelName.IsEmpty())
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*NextLevelName));
	}
}

void AEndStageTriggerBox::EndStage()
{
	if (UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>())
	{
		StageSubsystem->EndStage();
	}
}
