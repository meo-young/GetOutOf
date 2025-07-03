#include "Character/GOOCharacter.h"
#include "EnhancedInputComponent.h"
#include "GetOutOf.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AGOOCharacter::AGOOCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(34.f, 90.0f);
	
	GetCharacterMovement()->MaxWalkSpeed = 250.0f;

	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	CameraComponent->SetupAttachment(GetMesh(), FName("head"));
	CameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->bEnableFirstPersonFieldOfView = true;
	CameraComponent->bEnableFirstPersonScale = true;
	CameraComponent->FirstPersonFieldOfView = 70.0f;
	CameraComponent->FirstPersonScale = 0.6f;
}

void AGOOCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction) EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGOOCharacter::MoveInput);
		else LOG(Warning, TEXT("MoveAction이 설정되지 않았습니다"));
		
		if (LookAction) EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGOOCharacter::LookInput);
		else LOG(Warning, TEXT("LookAction이 설정되지 않았습니다"));
	}
	else
	{
		LOG(Warning, TEXT("EnhancedInputComponent가 유효하지 않습니다"));
	}
}

void AGOOCharacter::MoveInput(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void AGOOCharacter::LookInput(const FInputActionValue& Value)
{
	const FVector2D LookDirection = Value.Get<FVector2D>();
	DoLook(LookDirection.Y, LookDirection.X);
}

void AGOOCharacter::DoMove(const float Forward, const float Right)
{
	if (GetController())
	{
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void AGOOCharacter::DoLook(const float Pitch, const float Yaw)
{
	if(GetController())
	{
		AddControllerPitchInput(Pitch);
		AddControllerYawInput(Yaw);
	}
}
