#include "AI/StealthCharacter.h"
#include "GetOutOf.h"
#include "Camera/CameraComponent.h"
#include "Character/GOOCharacter.h"
#include "Character/Component/InteractionComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Define/DefineClass.h"
#include "SubSystem/StageSubSystem.h"

AStealthCharacter::AStealthCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	EventTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Event Trigger Box"));
	EventTriggerBox->SetupAttachment(GetRootComponent());
	EventTriggerBox->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	EventTriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	EventTriggerBox->SetCollisionResponseToChannel(ECC_INTERACTION, ECR_Block);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Dead Scene Camera"));
	CameraComponent->SetupAttachment(GetMesh());
}

void AStealthCharacter::BeginPlay()
{
	Super::BeginPlay();

	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(GetWorld()->GetFirstPlayerController()->GetPawn());

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnPlayerOverlapped);

	if (UInteractionComponent* InteractionComponent = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UInteractionComponent>())
	{
		InteractionComponent->OnInteractionEndedDelegate.AddDynamic(this, &ThisClass::DisableCollision);
	}

	if (UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>())
	{
		StageSubsystem->OnStageEndedDelegate.AddDynamic(this, &ThisClass::DestroyItem);
	}

	StopAnimation();
}

bool AStealthCharacter::CheckAllConditions()
{
	bIsInPlayerSight = !IsOutOfPlayerSight() && !IsObstacleBetweenPlayer();
	return bIsInPlayerSight;
}

bool AStealthCharacter::IsOutOfPlayerSight()
{
	const FVector PlayerForward = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorForwardVector();
	const FVector ToAI = (GetActorLocation() - GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()).GetSafeNormal();

	const float Dot = FVector::DotProduct(PlayerForward, ToAI);
	const float ViewingAngle = FMath::Acos(Dot) * (180.f / PI);
	
	if (ViewingAngle <= AcceptanceRadius)
	{
		return false;
	}
	
	return true;
}

bool AStealthCharacter::IsObstacleBetweenPlayer()
{
	const FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	const FVector AILocation = GetActorLocation();

	const bool bIsHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		AILocation,
		PlayerLocation,
		ECC_Visibility,
		CollisionParams
		);

	if (bIsHit)
	{
		return true;
	}

	return false;
}

void AStealthCharacter::StopAnimation()
{
	GetMesh()->SetPlayRate(0.0f);
}

void AStealthCharacter::ResumeAnimation()
{
	GetMesh()->SetPlayRate(1.0f);
}

void AStealthCharacter::Interact_Implementation()
{
	IInteractable::Interact_Implementation();

	if (OnInteractionStartDelegate.IsBound())
	{
		OnInteractionStartDelegate.Broadcast();
	}
}

void AStealthCharacter::DisableCollision()
{
	if (IsValid(EventTriggerBox))
	{
		EventTriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AStealthCharacter::DestroyItem()
{
	if (IsValid(this))
	{
		Destroy();
	}
}

void AStealthCharacter::OnPlayerOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsActivated) return;
	
	LOG2(TEXT("Actor : %s"), *OtherActor->GetName());
	if (OtherActor && OtherActor->IsA<AGOOCharacter>())
	{
		LOG2(TEXT("플레이어 닿음"));
		ShowDeadScene();
	}
}


