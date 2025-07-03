#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GOOCharacter.generated.h"

class UCameraComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class GETOUTOF_API AGOOCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGOOCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** W,A,S,D 입력 처리 함수 */ 
	void MoveInput(const FInputActionValue& Value);

	/** 마우스 입력 처리 함수 */
	void LookInput(const FInputActionValue& Value);

	/** 이동 로직 담당 함수 */
	void DoMove(const float Forward, const float Right);

	/** 마우스 회전 로직 담당 함수 */
	void DoLook(const float Pitch, const float Yaw);

protected:
	/** 이동 InputAction */
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* MoveAction = nullptr;

	/** 마우스 InputAction */
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* LookAction = nullptr;

private:
	UPROPERTY(VisibleAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	UCameraComponent* CameraComponent;
	
};
