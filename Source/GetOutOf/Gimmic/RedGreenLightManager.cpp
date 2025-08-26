#include "Gimmic/RedGreenLightManager.h"
#include "GetOutOf.h"
#include "Define/DefineClass.h"
#include "GameFramework/Character.h"
#include "Item/InteractableItem.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystem/SoundSubSystem.h"

ARedGreenLightManager::ARedGreenLightManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARedGreenLightManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsGameStarted || !bIsRedLight) return;

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!Player->GetVelocity().IsNearlyZero())
	{
		ShowJumpScare();
		FinishGame();
		LOG2(TEXT("플레이어 이동 감지"));
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FRotator CurrentControlRotation = PlayerController->GetControlRotation();
	if (!CurrentControlRotation.Equals(PreviousControlRotation, 0.2f))
	{
		ShowJumpScare();
		FinishGame();
		LOG2(TEXT("플레이어 시점 이동 감지"));
	}
}

void ARedGreenLightManager::StartRedGreenLight()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	USoundSubSystem* SoundSubSystem = GetGameInstance()->GetSubsystem<USoundSubSystem>();
	SoundSubSystem->PlayVoiceSFX(EVoiceType::LetsPlay, Player->GetActorLocation());

	SpawnDollItem();
	
	bIsGameStarted = true;
	GetWorldTimerManager().SetTimer(RedGreenLightTimer, this, &ThisClass::UpdateRedGreenLight, 3.0f, false);
}

void ARedGreenLightManager::FinishGame()
{
	GetWorldTimerManager().ClearTimer(RedGreenLightTimer);
	GetWorldTimerManager().ClearTimer(ActivateRedLightTimer);
	bIsGameStarted = false;
	bIsRedLight = false;
}

void ARedGreenLightManager::UpdateRedGreenLight()
{
	if (!bIsRedLight)
	{
		HandleRedLight();
	}
	else
	{
		HandleGreenLight();
	}
}

void ARedGreenLightManager::HandleRedLight()
{
	GetWorldTimerManager().SetTimer(ActivateRedLightTimer, [this]()
	{
		const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PreviousControlRotation = PlayerController->GetControlRotation();
		bIsRedLight = true;
	}, 0.5f, false);

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	USoundSubSystem* SoundSubSystem = GetGameInstance()->GetSubsystem<USoundSubSystem>();
	SoundSubSystem->PlayVoiceSFX(EVoiceType::RedLight, Player->GetActorLocation());
	
	InvokeRedGreenLightUpdateRandomly();
}

void ARedGreenLightManager::HandleGreenLight()
{
	bIsRedLight = false;

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	USoundSubSystem* SoundSubSystem = GetGameInstance()->GetSubsystem<USoundSubSystem>();
	SoundSubSystem->PlayVoiceSFX(EVoiceType::GreenLight, Player->GetActorLocation());

	InvokeRedGreenLightUpdateRandomly();
}

void ARedGreenLightManager::InvokeRedGreenLightUpdateRandomly()
{
	uint8 RandNum = FMath::RandRange(2, 5);
	GetWorldTimerManager().SetTimer(RedGreenLightTimer, this, &ThisClass::UpdateRedGreenLight, RandNum, false);
}

void ARedGreenLightManager::SpawnDollItem()
{
	DollItemInstance = GetWorld()->SpawnActor<AInteractableItem>(DollItemClass, FVector(9651.0f, 5423.0f, 63.0f), FRotator(0.0f, -180.0f, 0.0f));
}

void ARedGreenLightManager::DestroyDollItem()
{
	if (DollItemInstance)
	{
		DollItemInstance->Destroy();
	}
}
