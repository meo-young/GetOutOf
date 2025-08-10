#include "Character/GOOCharacter.h"
#include "EnhancedInputComponent.h"
#include "GetOutOf.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Component/InteractionComponent.h"
#include "Component/PostProcessEffectComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/SpotLightComponent.h"
#include "Core/GOOPlayerController.h"
#include "Define/DefineClass.h"
#include "Engine/SpotLight.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SubSystem/SoundSubSystem.h"
#include "SubSystem/StageSubSystem.h"
#include "UI/CrossHairWidget.h"
#include "UI/InventoryWidget.h"
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

	// Spring Arm 컴포넌트 생성 및 설정
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(CameraComponent);
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bEnableCameraRotationLag = true;

	// Spot Light 생성 및 설정
	FlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLight"));
	FlashLight->SetupAttachment(SpringArmComponent);
	

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

		if (SprintAction)
		{
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ThisClass::DoSprint);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::StopSprint);
		}
		else
		{
			LOG(Warning, TEXT("SprintAction이 설정되지 않았습니다"));
		}

		if (FlashAction)
		{
			EnhancedInputComponent->BindAction(FlashAction, ETriggerEvent::Started, this, &ThisClass::FlashLightInput);
		}
		else
		{
			LOG(Warning, TEXT("FlashAction이 설정되지 않았습니다"));
		}

		if (DoorAction)
		{
			EnhancedInputComponent->BindAction(DoorAction, ETriggerEvent::Started, this, &ThisClass::OpenDoor);
		}
		else
		{
			LOG(Warning, TEXT("DoorAction이 설정되지 않았습니다"));
		}

		/*if (InventoryAction)
		{
			EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ThisClass::InventoryInput);
		}
		else
		{
			LOG(Warning, TEXT("SprintAction이 설정되지 않았습니다"));
		}*/
	}
	else
	{
		LOG(Warning, TEXT("EnhancedInputComponent가 유효하지 않습니다"));
	}
}

void AGOOCharacter::BeginPlay()
{
	Super::BeginPlay();

	LOG2(TEXT("BeginPlay"));
	
	if (IsValid(InteractionComponent))
	{
		InteractionComponent->OnInteractionStartedDelegate.AddUObject(this, &ThisClass::DisablePlayerInput);
		InteractionComponent->OnInteractionEndedDelegate.AddDynamic(this, &ThisClass::EnablePlayerInput);
	}	

	if (UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>())
	{
		StageSubsystem->OnStageStartedDelegate.AddDynamic(this, &ThisClass::AGOOCharacter::StopFlashLightWithoutSound);
	}
}

void AGOOCharacter::DisablePlayerInput()
{
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	DisableInput(Cast<APlayerController>(GetController()));
}

void AGOOCharacter::EnablePlayerInput()
{
	EnableInput(Cast<APlayerController>(GetController()));
}

void AGOOCharacter::SetDeadMode()
{
	// 플레이어의 입력과 애니메이션을 비활성화하고 RagDoll을 활성화 합니다.
	DisablePlayerInput();
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->GetAnimInstance()->EnableUpdateAnimation(false);

	// 카메라의 기본 설정들을 비활성화 합니다.
	CameraComponent->bUsePawnControlRotation = false;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;

	// 사망 사운드를 재생합니다.
	/*FTimerHandle DeadSoundHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadSoundHandle, FTimerDelegate::CreateLambda([this]()
	{
		USoundSubSystem* SoundSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<USoundSubSystem>();
		SoundSubsystem->PlaySFX(ESFX::BodyFall, GetActorLocation() + FVector(0.0f, 0.0f, 10.0f));
	}), 0.5f, false);*/

	// 2초 후 RagDoll을 비활성화 합니다.
	FTimerHandle SimulatedPhysicsHandle;
	GetWorld()->GetTimerManager().SetTimer(SimulatedPhysicsHandle, FTimerDelegate::CreateLambda([this]()
	{
		CameraComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}), 2.0f, false);
}

void AGOOCharacter::SetNormalMode()
{
}

void AGOOCharacter::MoveInput(const FInputActionValue& Value)
{
	if (!bIsEnableMove) return;
	
	const FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void AGOOCharacter::LookInput(const FInputActionValue& Value)
{
	if (!bIsEnableLook) return;
	
	const FVector2D LookDirection = Value.Get<FVector2D>();
	DoLook(LookDirection.Y, LookDirection.X);
}

void AGOOCharacter::InteractInput(const FInputActionValue& Value)
{
	if (!bIsEnableInteract || !InteractionComponent->IsInteracting()) return;
	
	DoInteract();
}

void AGOOCharacter::FlashLightInput(const FInputActionValue& Value)
{
	if (!bIsEnableFlashLight) return;
	
	if (bIsFlashLightOn)
	{
		StopFlashLight();
	}
	else
	{
		DoFlashLight();
	}
}

void AGOOCharacter::InventoryInput(const FInputActionValue& Value)
{
	if (!bIsEnableInventory) return;
	
	if (bIsInventoryWidgetOpen)
	{
		RemoveInventoryWidget();
	}
	else
	{
		AddInventoryWidget();
	}
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

void AGOOCharacter::DoSprint()
{
	if (!bIsEnableSprint) return;
	
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void AGOOCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

void AGOOCharacter::DoFlashLight()
{
	if (USoundSubSystem* SoundSubsystem = GetGameInstance()->GetSubsystem<USoundSubSystem>())
	{
		SoundSubsystem->PlaySFX(ESFX::SwitchOn, GetActorLocation(), FRotator::ZeroRotator);
	}
	
	bIsFlashLightOn = true;
	FlashLight->SetVisibility(true);
}

void AGOOCharacter::StopFlashLight()
{
	if (USoundSubSystem* SoundSubsystem = GetGameInstance()->GetSubsystem<USoundSubSystem>())
	{
		SoundSubsystem->PlaySFX(ESFX::SwitchOff, GetActorLocation(), FRotator::ZeroRotator);
	}
	
	bIsFlashLightOn = false;
	FlashLight->SetVisibility(false);
}

void AGOOCharacter::OpenDoor()
{
	if (!IsValid(InteractionComponent))
	{
		LOG(Warning, TEXT("InteractionComponent가 유효하지 않습니다"));
		return;
	}
	
	InteractionComponent->DoorInteraction();
}

void AGOOCharacter::StopFlashLightWithoutSound()
{
	bIsFlashLightOn = false;
	FlashLight->SetVisibility(false);
}

void AGOOCharacter::AddInventoryWidget()
{
	if (AGOOPlayerController* PlayerController = Cast<AGOOPlayerController>(GetController()))
	{
		if (UInventoryWidget* InventoryWidget = PlayerController->GetInventoryWidget())
		{
			if (!InventoryWidget->IsInViewport())
			{
				SetEnableFlashLight(false);
				SetEnableInteract(false);
				SetEnableMove(false);
				SetEnableSprint(false);
				SetEnableLook(false);

				PlayerController->SetInputMode(FInputModeUIOnly());
				PlayerController->SetShowMouseCursor(false);
				
				InventoryWidget->AddToViewport();
				bIsInventoryWidgetOpen = true;

				if (USoundSubSystem* SoundSubsystem = GetGameInstance()->GetSubsystem<USoundSubSystem>())
				{
					SoundSubsystem->PlaySFX2D(ESFX::DiaryOpen);
				}
			}
		}
	}
}

void AGOOCharacter::RemoveInventoryWidget()
{
	SetEnableFlashLight(true);
	SetEnableInteract(true);
	SetEnableMove(true);
	SetEnableSprint(true);
	SetEnableLook(true);

	AGOOPlayerController* PlayerController = Cast<AGOOPlayerController>(GetController());
	PlayerController->SetInputMode(FInputModeGameOnly());

	bIsInventoryWidgetOpen = false;	
}
