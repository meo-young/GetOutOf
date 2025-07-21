#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GOOCharacter.generated.h"

class USpotLightComponent;
class USpringArmComponent;
class UPostProcessEffectComponent;
class UPlayerHUDWidget;
class UInteractionComponent;
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
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void DisablePlayerInput();

	UFUNCTION(BlueprintCallable)
	void EnablePlayerInput();

	/** Inventory Widget을 제거하는 로직 함수 */
	void RemoveInventoryWidget(); 

protected:
	/** W,A,S,D 입력 처리 함수 */ 
	void MoveInput(const FInputActionValue& Value);

	/** 마우스 입력 처리 함수 */
	void LookInput(const FInputActionValue& Value);

	/** 마우스 클릭 입력 처리 함수 */
	void InteractInput(const FInputActionValue& Value);
	
	/** "F"키 입력 처리 함수 */
	void FlashLightInput(const FInputActionValue& Value);

	/** "Tab"키 입력 처리 함수 */
	void InventoryInput(const FInputActionValue& Value);
	
	/** 이동 로직 담당 함수 */
	void DoMove(const float Forward, const float Right);

	/** 마우스 회전 로직 담당 함수 */
	void DoLook(const float Pitch, const float Yaw);

	/** 마우스 클릭 로직 함수 */
	void DoInteract();

	/** Sprint 로직 함수 */
	void DoSprint();

	/** Sprint 종료 로직 함수 */
	void StopSprint();

	/** FlashLight을 켜는 로직 함수 */
	void DoFlashLight();

	/** FlashLight을 끄는 로직 함수 */
	void StopFlashLight();

	/** Inventory Widget을 생성하는 로직 함수 */
	void AddInventoryWidget();

	/** 사운드 없이 후레쉬를 비활성화 하는 함수 */
	UFUNCTION()
	void StopFlashLightWithoutSound();

protected:
	/** 이동 InputAction */
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* MoveAction = nullptr;

	/** 마우스 InputAction */
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* LookAction = nullptr;

	/** 마우스 클릭 Action */
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* InteractAction = nullptr;

	/** Shift 클릭 Action */
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* SprintAction = nullptr;

	/** F 클릭 Action */
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* FlashAction = nullptr;

	/** Tab 클릭 Action */
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* InventoryAction = nullptr;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UPostProcessEffectComponent* PostProcessEffectComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USpotLightComponent* FlashLight;

private:
	uint8 bIsEnableMove : 1 = true;
	uint8 bIsEnableSprint : 1 = true;
	uint8 bIsEnableLook : 1 = true;
	uint8 bIsEnableInteract : 1 = true;
	uint8 bIsEnableFlashLight : 1 = true;
	uint8 bIsFlashLightOn : 1 = false;
	uint8 bIsEnableInventory : 1 = true;
	uint8 bIsInventoryWidgetOpen : 1 = false;
	
public:
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	FORCEINLINE UInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }

	FORCEINLINE void SetEnableMove(const bool bIsEnable) { bIsEnableMove = bIsEnable; }
	FORCEINLINE void SetEnableSprint(const bool bIsEnable) { bIsEnableSprint = bIsEnable; GetCharacterMovement()->MaxWalkSpeed = 150.0f; }
	FORCEINLINE void SetEnableInteract(const bool bIsEnable) { bIsEnableInteract = bIsEnable; }
	FORCEINLINE void SetEnableFlashLight(const bool bIsEnable) { bIsEnableFlashLight = bIsEnable; }
	FORCEINLINE void SetEnableInventory(const bool bIsEnable) { bIsEnableInventory = bIsEnable; }
	FORCEINLINE void SetEnableLook(const bool bIsEnable) { bIsEnableLook = bIsEnable; }
	
};
