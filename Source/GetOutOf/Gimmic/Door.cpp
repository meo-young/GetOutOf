#include "Gimmic/Door.h"

#include "Character/GOOCharacter.h"
#include "Components/BoxComponent.h"
#include "Core/GOOGameModeBase.h"
#include "Define/DefineClass.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystem/SoundSubSystem.h"
#include "Subsystem/StageSubSystem.h"

ADoor::ADoor()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(SceneComponent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	DoorMesh->SetupAttachment(SceneComponent);

	GlassMesh = CreateDefaultSubobject<UStaticMeshComponent>("GlassMesh");
	GlassMesh->SetupAttachment(DoorMesh);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxComponent->SetupAttachment(DoorMesh);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_DOOR, ECR_Block);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>();
	StageSubsystem->OnStageStartedDelegate.AddDynamic(this, &ThisClass::LockDoor);
	StageSubsystem->OnStageClearedDelegate.AddDynamic(this, &ThisClass::UnLockDoor);
}

void ADoor::UnLockDoor()
{
	USoundSubSystem* SoundSubsystem = GetGameInstance()->GetSubsystem<USoundSubSystem>();
	SoundSubsystem->PlaySFX(ESFX::UnlockDoor, GetActorLocation(), FRotator::ZeroRotator);

	DoorMesh->SetCollisionResponseToChannel(ECC_DOOR, ECR_Block);
}

void ADoor::LockDoor()
{
	DoorMesh->SetCollisionResponseToChannel(ECC_DOOR, ECR_Ignore);
}

void ADoor::Interact_Implementation()
{
	IInteractable::Interact_Implementation();

	// 플레이어 입력 비활성화
	Cast<AGOOCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())->DisablePlayerInput();

	// 문을 여는 애니메이션 재생
	PlayDoorOpenAnimation();

	// 타이머에 필요한 변수 캐스팅
	UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>();
	AGOOGameModeBase* GameMode = Cast<AGOOGameModeBase>(GetWorld()->GetAuthGameMode());

	// 타이머 활성화
	const uint8 CurrentStageNum = StageSubsystem->GetCurrentStageNum();
	if (CurrentStageNum == 3 || CurrentStageNum == 6)
	{
		GetWorldTimerManager().SetTimer(RestartTimer, FTimerDelegate::CreateLambda([this]
		{
			UGameplayStatics::OpenLevel(GetWorld(), NextStageName);
		}), 6.5f, false);
		
		}
	else
	{
		GetWorldTimerManager().SetTimer(RestartTimer, GameMode, &AGOOGameModeBase::ReStart, 6.5f, false);
		GetWorldTimerManager().SetTimer(StartStageTimer, StageSubsystem, &UStageSubSystem::StartStage, 7.0f, false);
	}
	GetWorldTimerManager().SetTimer(EndStageTimer, StageSubsystem, &UStageSubSystem::EndStage, 3.0f, false);
}



