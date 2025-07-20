#include "Item/Duck.h"
#include "GetOutOf.h"
#include "Character/GOOCharacter.h"

ADuck::ADuck()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADuck::BeginPlay()
{
	Super::BeginPlay();

	Player = GetWorld()->GetFirstPlayerController()->GetCharacter();
}

void ADuck::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsRotating && Player)
	{
		RotateDuck(DeltaSeconds);
	}
}

void ADuck::Interact_Implementation()
{
	Super::Interact_Implementation();
	
	bIsRotating = true;
}

void ADuck::RotateDuck(const float DeltaSeconds)
{
	if (!IsValid(Player)) return;
	
	const FVector CurrentLocation = GetActorLocation();
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector Direction = (PlayerLocation - CurrentLocation).GetSafeNormal();

	const FRotator TargetRotation = Direction.Rotation();
	const FRotator CurrentRotation = GetActorRotation();

	// 현재 회전에서 타겟 회전으로 부드럽게 보간
	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, RotationSpeed);

	SetActorRotation(NewRotation);
}
