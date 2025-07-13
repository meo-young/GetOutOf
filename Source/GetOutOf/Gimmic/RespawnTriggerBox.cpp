#include "Gimmic/RespawnTriggerBox.h"
#include "EngineUtils.h"
#include "GetOutOf.h"
#include "Camera/CameraComponent.h"
#include "Character/GOOCharacter.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/PlayerStart.h"
#include "SubSystem/StageSubSystem.h"

void ARespawnTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActorBeginOverlap);
	GetCollisionComponent()->SetGenerateOverlapEvents(true);
}

void ARespawnTriggerBox::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (AGOOCharacter* Player = Cast<AGOOCharacter>(OtherActor))
		{
			LOG(Warning, TEXT("플레이어 충돌"));
			for (APlayerStart* PlayerStart : TActorRange<APlayerStart>(GetWorld()))
			{
				if (PlayerStart)
				{
					Player->SetActorTransform(PlayerStart->GetActorTransform());
					Player->GetController()->SetControlRotation(FRotator::ZeroRotator);

					UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>();
					StageSubsystem->StartStage();
				}
			}
		}
	}
}
