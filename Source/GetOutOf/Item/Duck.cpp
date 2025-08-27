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

	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(Player);
}

void ADuck::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (bIsRotating && Player)
	{
		RotateDuck(DeltaSeconds);
		CheckIfPlayerLookingAtDuck(DeltaSeconds);
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

void ADuck::CheckIfPlayerLookingAtDuck(const float DeltaSeconds)
{
	if (!IsValid(Player) || bHasLooked) return;
	
	// 1. 플레이어 -> 오리 방향 벡터
	FVector DirectionToDuck = (GetActorLocation() - Player->GetActorLocation()).GetSafeNormal();

	// 2. 플레이어의 카메라 forward 벡터 가져오기
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	Player->GetActorEyesViewPoint(PlayerViewLocation, PlayerViewRotation);
	FVector PlayerForward = PlayerViewRotation.Vector();

	// 3. 시야각 계산
	float Dot = FVector::DotProduct(PlayerForward, DirectionToDuck);
	float Angle = FMath::Acos(Dot) * (180.f / PI); // 라디안 → 도

	if (Angle <= ViewAngleThreshold)
	{
		// 4. 장애물 검사 (LineTrace)
		bool bHit = GetWorld()->LineTraceSingleByChannel(
			Hit,
			PlayerViewLocation,
			GetActorLocation(),
			TraceChannel,
			Params
		);

		if (!bHit || Hit.GetActor() == this)
		{
			// 플레이어가 제대로 응시 중
			LookAtTime += DeltaSeconds;

			if (LookAtTime >= RequiredLookTime)
			{
				if (OnEventStartDelegate.IsBound())
				{
					OnEventStartDelegate.Broadcast();
				}
				bHasLooked = true;
			}
			return;
		}
	}

	// 조건 만족 못 하면 리셋
	LookAtTime = 0.0f;
}
