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

private:
	/** 오리 회전 속도 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float RotationSpeed = 1.0f;
	
	/** 플레이어 캐싱 변수 */
	UPROPERTY()
	TObjectPtr<ACharacter> Player = nullptr;

	/** 회전 중인지를 나타내는 변수 */
	uint8 bIsRotating : 1 = false;
	
};
