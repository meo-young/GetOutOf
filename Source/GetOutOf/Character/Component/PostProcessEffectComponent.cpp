#include "Character/Component/PostProcessEffectComponent.h"
#include "GetOutOf.h"
#include "InteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/GOOCharacter.h"

UPostProcessEffectComponent::UPostProcessEffectComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPostProcessEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	AGOOCharacter* Player = Cast<AGOOCharacter>(GetOwner());

	// 플레이어 카메라의 PostProcessSettings를 설정
	PlayerCameraComponent = Player->GetCameraComponent();
	PlayerCameraComponent->PostProcessSettings.bOverride_AutoExposureBias = true;

	// InteractionComponent의 상호작용 종료 델리게이트에 함수 바인딩
	UInteractionComponent* InteractionComponent = Player->GetInteractionComponent();
	InteractionComponent->OnInteractionEndedDelegate.AddUObject(this, &ThisClass::ShowExposureEffect);
}

void UPostProcessEffectComponent::ShowExposureEffect()
{
	CurrentExposure = 7.0f;

	// Bloom 초기값 설정
	PlayerCameraComponent->PostProcessSettings.bOverride_AutoExposureBias = true;
	PlayerCameraComponent->PostProcessSettings.AutoExposureBias = CurrentExposure;

	// 타이머 설정
	GetOwner()->GetWorldTimerManager().SetTimer(ExposureTimerHandle, this, &ThisClass::UpdateExposure, 0.016f, true);
}

void UPostProcessEffectComponent::UpdateExposure()
{
	ExposureLerpTimer += 0.016f;
	const float Alpha = FMath::Clamp(ExposureLerpTimer / 2.0f, 0.0f, 1.0f);
    
	CurrentExposure = FMath::Lerp(7.0f, 1.0f, Alpha);
	PlayerCameraComponent->PostProcessSettings.AutoExposureBias = CurrentExposure;
	
	if (Alpha >= 1.0f)
	{
		ExposureLerpTimer = 0.0f;
		PlayerCameraComponent->PostProcessSettings.AutoExposureBias = 0.25f;
		PlayerCameraComponent->PostProcessSettings.bOverride_AutoExposureBias = false;

		GetOwner()->GetWorldTimerManager().ClearTimer(ExposureTimerHandle);
	}
}

