#include "Gimmic/RedGreenLightManager.h"
#include "GetOutOf.h"
#include "Define/DefineClass.h"
#include "GameFramework/Character.h"
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
		LOG2(TEXT("플레이어 이동 감지"));
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FRotator CurrentControlRotation = PlayerController->GetControlRotation();
	if (!CurrentControlRotation.Equals(PreviousControlRotation, 0.1f))
	{
		LOG2(TEXT("플레이어 시점 이동 감지"));
	}
}

void ARedGreenLightManager::StartRedGreenLight()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	USoundSubSystem* SoundSubSystem = GetGameInstance()->GetSubsystem<USoundSubSystem>();
	SoundSubSystem->PlayVoiceSFX(EVoiceType::LetsPlay, Player->GetActorLocation());
	
	bIsGameStarted = true;
	GetWorldTimerManager().SetTimer(RedGreenLightTimer, this, &ThisClass::UpdateRedGreenLight, 5.0f, false);
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
	FTimerHandle ActivateRedLightTimer;
	GetWorldTimerManager().SetTimer(ActivateRedLightTimer, [this]()
	{
		bIsRedLight = true;
	}, 0.75f, false);

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	USoundSubSystem* SoundSubSystem = GetGameInstance()->GetSubsystem<USoundSubSystem>();
	SoundSubSystem->PlayVoiceSFX(EVoiceType::RedLight, Player->GetActorLocation());

	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PreviousControlRotation = PlayerController->GetControlRotation();
	
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
