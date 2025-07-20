#pragma once

#include "CoreMinimal.h"
#include "Item/InteractableItem.h"
#include "Balloon.generated.h"

UCLASS()
class GETOUTOF_API ABalloon : public AInteractableItem
{
	GENERATED_BODY()

public:
	ABalloon();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
 	virtual void Interact_Implementation() override;

private:
	/** 풍선의 움직임을 구현한 함수 */
	void FloatUp(const float DeltaSeconds);

private:
	/** 풍선 초기 위치 */
	FVector InitialLocation = FVector::ZeroVector;

	/** 측정 시간 */
	float ElapsedTime = 0.0f;

	float Amplitude = 5.0f;           // 위아래 이동 거리
    float Period = 4.0f;              // 위+아래가 2초니까 각 방향은 1초
	
};
