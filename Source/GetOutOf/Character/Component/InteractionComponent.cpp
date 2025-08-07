#include "Character/Component/InteractionComponent.h"
#include "GetOutOf.h"
#include "Camera/CameraComponent.h"
#include "Character/GOOCharacter.h"
#include "Define/DefineClass.h"
#include "Interface/Interactable.h"
#include "SubSystem/SoundSubSystem.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	QueryParams.AddIgnoredActor(GetOwner());
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	const UCameraComponent* CameraComponent = GetOwner()->FindComponentByClass<UCameraComponent>();
	if (!IsValid(CameraComponent))
	{
		LOG(Warning, TEXT("InteractionComponent의 Owner에 CameraComponent가 없습니다"));
		return;
	}

	const FVector CurrentLocation = CameraComponent->GetComponentLocation();
	const FVector ForwardVector = CameraComponent->GetForwardVector();
	const FVector TargetLocation = CurrentLocation + (ForwardVector * 300.0f);
	
	const bool bHit = GetWorld()->LineTraceSingleByChannel(
		InteractionHitResult,
		CurrentLocation,
		TargetLocation,
		ECC_INTERACTION,
		QueryParams
		);

	const bool bDHit = GetWorld()->LineTraceSingleByChannel(
		DoorHitResult,
		CurrentLocation,
		TargetLocation,
		ECC_DOOR,
		QueryParams
		);

	if (bHit)
	{
		if (!bIsInteracting)
		{
			OnInteractionPossibleDelegate.Broadcast();
		}
		
		bIsInteracting = true;
	}
	else
	{
		if (bIsInteracting)
		{
			OnInteractionImpossibleDelegate.Broadcast();
		}

		bIsInteracting = false;
	}
}

void UInteractionComponent::StartInteraction()
{
	// 상호작용 오브젝트 캐스팅
	InteractableObject = Cast<IInteractable>(InteractionHitResult.GetActor());
	
	// 카메라 '삐빗' 소리 재생
	USoundSubSystem* SoundSubSystem = GetWorld()->GetGameInstance()->GetSubsystem<USoundSubSystem>();
	SoundSubSystem->PlaySFX(ESFX::CameraBeep, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);

	// 상호작용 시작 델리게이트 호출
	if (OnInteractionStartedDelegate.IsBound())
	{
		LOG2(TEXT("호출"));
		OnInteractionStartedDelegate.Broadcast();
	}

	// 카메라 플래시 효과 출력 및 일지 기록
	GetOwner()->GetWorldTimerManager().SetTimer(CameraTimerHandle, this, &ThisClass::EndInteraction, 1.5f, false);
}

void UInteractionComponent::DoorInteraction()
{
	// 상호작용 오브젝트 캐스팅
	InteractableObject = Cast<IInteractable>(DoorHitResult.GetActor());

	// 상호작용 오브젝트가 유효하다면 상호작용 함수 호출
	if (InteractableObject)
	{
		IInteractable::Execute_Interact(InteractableObject->_getUObject());
	}
}

void UInteractionComponent::EndInteraction()
{
	// 상호작용 오브젝트가 유효하다면 상호작용 함수 호출
	if (InteractableObject)
	{
		IInteractable::Execute_Interact(InteractableObject->_getUObject());
	}
	
	// 카메라 플래시 효과음 재생
	USoundSubSystem* SoundSubSystem = GetWorld()->GetGameInstance()->GetSubsystem<USoundSubSystem>();
	SoundSubSystem->PlaySFX(ESFX::CameraFlash, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);

	// 상호작용 종료 델리게이트 호출
	if (OnInteractionEndedDelegate.IsBound())
	{
		OnInteractionEndedDelegate.Broadcast();
	}
}
