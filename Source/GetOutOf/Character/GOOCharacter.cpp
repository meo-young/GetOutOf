#include "Character/GOOCharacter.h"
#include "EnhancedInputComponent.h"
#include "GetOutOf.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Component/InteractionComponent.h"
#include "Component/PostProcessEffectComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PostProcessComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SubSystem/SoundSubSystem.h"
#include "UI/CrossHairWidget.h"
#include "UI/PlayerHUDWidget.h"

AGOOCharacter::AGOOCharacter()
{
	// 캡슐 컴포넌트 사이즈 조절
	GetCapsuleComponent()->InitCapsuleSize(34.f, 90.0f);

	// 캐릭터 이동속도 제한
	GetCharacterMovement()->MaxWalkSpeed = 250.0f;

	// 1인칭 메쉬 설정
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;

	// 1인칭 카메라 컴포넌트 생성 및 설정
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	CameraComponent->SetupAttachment(GetMesh(), FName("head"));
	CameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->bEnableFirstPersonFieldOfView = true;
	CameraComponent->bEnableFirstPersonScale = true;
	CameraComponent->FirstPersonFieldOfView = 70.0f;
	CameraComponent->FirstPersonScale = 0.6f;

	// Interaction 컴포넌트 생성
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));

	// PostProcessEffect 컴포넌트 생성
	PostProcessEffectComponent = CreateDefaultSubobject<UPostProcessEffectComponent>(TEXT("PostProcessEffectComponent"));
}

void AGOOCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::MoveInput);
		}
		else
		{
			LOG(Warning, TEXT("MoveAction이 설정되지 않았습니다"));
		}
		
		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::LookInput);
		}
		else
		{
			LOG(Warning, TEXT("LookAction이 설정되지 않았습니다"));
		}

		if (InteractAction)
		{
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ThisClass::InteractInput);
		}
		else
		{
			LOG(Warning, TEXT("InteractAction이 설정되지 않았습니다"));
		}
	}
	else
	{
		LOG(Warning, TEXT("EnhancedInputComponent가 유효하지 않습니다"));
	}
}

void AGOOCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Player HUD 위젯 인스턴스 생성 및 뷰포트에 추가
	if (IsValid(PlayerHUDWidgetClass))
	{
		PlayerHUDWidgetInstance = CreateWidget<UPlayerHUDWidget>(GetWorld(), PlayerHUDWidgetClass);
		if (IsValid(PlayerHUDWidgetInstance))
		{
			if (!PlayerHUDWidgetInstance->IsInViewport())
			{
				LOG(Log,TEXT("PlayerHUDWidget 인스턴스 생성 성공"));
				PlayerHUDWidgetInstance->AddToViewport();	
			}
		}
	}
}

void AGOOCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(InteractionComponent))
	{
		if (UCrossHairWidget* CrossHairWidget = PlayerHUDWidgetInstance->GetCrossHairWidget())
		{
			InteractionComponent->OnInteractionPossibleDelegate.AddUObject(CrossHairWidget, &UCrossHairWidget::SetCrossHairImageToRed);
			InteractionComponent->OnInteractionImpossibleDelegate.AddUObject(CrossHairWidget, &UCrossHairWidget::SetCrossHairImageToWhite);
			InteractionComponent->OnInteractionStartedDelegate.AddUObject(this, &ThisClass::DisablePlayerInput);
			InteractionComponent->OnInteractionEndedDelegate.AddUObject(this, &ThisClass::EnablePlayerInput);
		}
	}
}

void AGOOCharacter::DisablePlayerInput()
{
	DisableInput(Cast<APlayerController>(GetController()));
}

void AGOOCharacter::EnablePlayerInput()
{
	EnableInput(Cast<APlayerController>(GetController()));
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

void AGOOCharacter::InteractInput(const FInputActionValue& Value)
{
	DoInteract();
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

void AGOOCharacter::DoInteract()
{
	if (!IsValid(InteractionComponent))
	{
		LOG(Warning, TEXT("InteractionComponent가 유효하지 않습니다"));
		return;
	}

	InteractionComponent->StartInteraction();
}
