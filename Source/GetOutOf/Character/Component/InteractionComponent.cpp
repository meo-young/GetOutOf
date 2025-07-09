#include "Character/Component/InteractionComponent.h"
#include "GetOutOf.h"
#include "Camera/CameraComponent.h"
#include "Character/GOOCharacter.h"
#include "Define/DefineClass.h"
#include "UI/CrossHairWidget.h"
#include "UI/PlayerHUDWidget.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	QueryParams.AddIgnoredActor(GetOwner());

	BindToInteractionStartDelegate();
	BindToInteractionEndedDelegate();
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
	const FVector TargetLocation = CurrentLocation + (ForwardVector * 250.0f);
	
	const bool bHit = GetWorld()->LineTraceSingleByChannel(
		InteractionHitResult,
		CurrentLocation,
		TargetLocation,
		ECC_INTERACTION,
		QueryParams
		);

#if WITH_EDITOR
	//DrawDebugLine(GetWorld(), CurrentLocation, TargetLocation, FColor::Green, false, -1.0f, 0, 1.0f);
#endif

	if (bHit)
	{
		if (!bIsInteracting)
		{
			OnInteractionStartedDelegate.Broadcast();
			// 히트된 액터 이름 출력 예시
			if (InteractionHitResult.GetActor())
			{
				LOG(Log, TEXT("Hit Actor: %s"), *InteractionHitResult.GetActor()->GetName());
			}	
		}
		
		bIsInteracting = true;
	}
	else
	{
		if (bIsInteracting)
		{
			OnInteractionEndedDelegate.Broadcast();
		}

		bIsInteracting = false;
	}
}

void UInteractionComponent::BindToInteractionStartDelegate()
{
	// 상호작용 시작 시 크로스헤어를 빨간색으로 변경
	if (AGOOCharacter* Player = Cast<AGOOCharacter>(GetOwner()))
	{
		if (UPlayerHUDWidget* PlayerHUDWidgetInstance = Player->GetPlayerHUDWidget())
		{
			if (UCrossHairWidget* CrossHairWidget = PlayerHUDWidgetInstance->GetCrossHairWidget())
			{
				LOG(Log, TEXT("Interaction 시작 델리게이트 바인딩 성공"));
				OnInteractionStartedDelegate.AddUObject(CrossHairWidget, &UCrossHairWidget::SetCrossHairImageToRed);
			}
		}
	}
}

void UInteractionComponent::BindToInteractionEndedDelegate()
{
	// 상호작용 종료 시 크로스헤어를 흰색으로 변경
	if (AGOOCharacter* Player = Cast<AGOOCharacter>(GetOwner()))
	{
		if (UPlayerHUDWidget* PlayerHUDWidgetInstance = Player->GetPlayerHUDWidget())
		{
			if (UCrossHairWidget* CrossHairWidget = PlayerHUDWidgetInstance->GetCrossHairWidget())
			{
				LOG(Log, TEXT("Interaction 끝 델리게이트 바인딩 성공"));
				OnInteractionEndedDelegate.AddUObject(CrossHairWidget, &UCrossHairWidget::SetCrossHairImageToWhite);
			}
		}
	}
}
