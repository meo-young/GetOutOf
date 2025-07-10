#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PostProcessEffectComponent.generated.h"

class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GETOUTOF_API UPostProcessEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPostProcessEffectComponent();
	virtual void BeginPlay() override;

public:
	/** 카메라 촬영 효과를 연출하는 함수 */
	void ShowExposureEffect();

	/** 카메라 노출 효과를 업데이트하는 함수 */
	void UpdateExposure();

private:
	/** 플레이어 카메라 컴포넌트 */
	UPROPERTY()
	UCameraComponent* PlayerCameraComponent;

	/** Exposure 효과를 위한 타이머 핸들 */
	FTimerHandle ExposureTimerHandle;

	/** Exposure 효과를 위한 보간 타이머 */
	float ExposureLerpTimer = 0.0f;

	/** 현재 노출 값 */
	float CurrentExposure = 0.0f;
	
};
