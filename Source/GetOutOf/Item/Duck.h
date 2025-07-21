#pragma once

#include "CoreMinimal.h"
#include "Item/InteractableItem.h"
#include "Duck.generated.h"

UCLASS()
class GETOUTOF_API ADuck : public AInteractableItem
{
	GENERATED_BODY()

public:
	ADuck();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void Interact_Implementation() override;

private:
	/** 오리를 플레이어 방향으로 회전시키는 함수 */
	void RotateDuck(const float DeltaSeconds);

	/** 플레이어가 오리를 쳐다보는 중인지 판단하는 함수 */
	void CheckIfPlayerLookingAtDuck(const float DeltaSeconds);

private:
	/** 오리 회전 속도 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float RotationSpeed = 1.0f;
	
	/** 플레이어 캐싱 변수 */
	UPROPERTY()
	TObjectPtr<ACharacter> Player = nullptr;

	/** 회전 중인지를 나타내는 변수 */
	uint8 bIsRotating : 1 = false;

	/** 플레이어가 오리를 바라보는 시간 */
	float LookAtTime = 0.0f;

	/** 한 번 Good 로그 출력 후 다시 출력하지 않기 위한 bool 변수 */
	uint8 bHasLooked : 1 = false;

	/** 쳐다봄으로 인지하는 회전 각 */
	float ViewAngleThreshold = 30.0f;

	/** 플레이어가 오리를 바라보는 시간 임계값 */
	float RequiredLookTime = 4.0f;

	/** 트레이스 채널 설정 */
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	FHitResult Hit;
	FCollisionQueryParams Params;
	
};
