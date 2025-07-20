#include "SubSystem/SoundSubSystem.h"
#include "GetOutOf.h"
#include "StageSubSystem.h"
#include "Character/GOOCharacter.h"
#include "Components/AudioComponent.h"
#include "Core/GOOPlayerController.h"
#include "DataTable/BGMDataTable.h"
#include "DataTable/SFXDataTable.h"
#include "DataTable/VoiceDataTable.h"
#include "Define/DefineClass.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "UI/DialogueWidget.h"

USoundSubSystem::USoundSubSystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SFX(TEXT("/Game/_GetOutOf/DataTable/DT_SFX"));
	if (DT_SFX.Succeeded())
	{
		SFXDataTable = DT_SFX.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BGM(TEXT("/Game/_GetOutOf/DataTable/DT_BGM"));
	if (DT_BGM.Succeeded())
	{
		BGMDataTable = DT_BGM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Voice(TEXT("/Game/_GetOutOf/DataTable/DT_Voice"));
	if (DT_Voice.Succeeded())
	{
		VoiceDataTable = DT_Voice.Object;
	}
}

void USoundSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// DataTable의 모든 데이터를 추출한다.
	SFXDataTable->GetAllRows<FSFXDataTable>(TEXT(""), SFXDataRows);
	BGMDataTable->GetAllRows<FBGMDataTable>(TEXT(""), BGMDataRows);
	VoiceDataTable->GetAllRows<FVoiceDataTable>(TEXT(""), VoiceDataRows);
}

void USoundSubSystem::PlayVoiceSFX(EVoiceType SFX, const FVector& InLocation)
{
	if (VoiceDataRows.Num() <= 0)
	{
		LOG(Error, TEXT("Voice Data Table이 유효하지 않습니다."));
		return;
	}

	USoundCue* SoundCue = VoiceDataRows[static_cast<int32>(SFX)]->Voice;
	if (!IsValid(SoundCue))
	{
		LOG(Error, TEXT("Voice Data Table에 정의된 SoundCue가 유효하지 않습니다."));
		return;
	}

	FText* DialogueText = &VoiceDataRows[static_cast<int32>(SFX)]->DialogueText;
	if (DialogueText->IsEmpty())
	{
		LOG(Error, TEXT("Voice Data Table에 정의된 DialogueText가 비어있습니다."));
		return;
	}

	if (AGOOPlayerController* PlayerController = Cast<AGOOPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (UDialogueWidget* DialogueWidget = PlayerController->GetDialogueWidget())
		{
			DialogueWidget->SetDialogueText(DialogueText->ToString());
		}
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCue, InLocation, FRotator::ZeroRotator);
}

void USoundSubSystem::PlaySFX(ESFX SFX, const FVector& InLocation, const FRotator& InRotator)
{
	// SFXDataRows가 유효한지 확인한다.
	if (SFXDataRows.Num() <= 0)
	{
		LOG(Error, TEXT("SFX Data Table이 유효하지 않습니다."));
		return;
	}

	// SFX Enum에 해당하는 사운드를 가져온다.
	USoundCue* SoundCue = SFXDataRows[static_cast<int32>(SFX)]->SoundCue;
	if (!IsValid(SoundCue))
	{
		LOG(Error, TEXT("SFX Data Table에 정의된 SoundCue가 유효하지 않습니다."));
		return;
	}

	// 0.8f에서 1.2f 사이의 랜덤 볼륨을 지정한다.
	const float VolumeMultiplier = FMath::RandRange(0.8f, 1.2f);

	// 공간 음향을 재생한다.
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCue, InLocation, InRotator, VolumeMultiplier, 1.0f, 0.0f);
}

void USoundSubSystem::PlayBGM(EBGM BGM)
{
	if (BGMDataRows.Num() <= 0)
	{
		LOG(Error, TEXT("BGM Data Table이 유효하지 않습니다."));
		return;
	}

	// SFX Enum에 해당하는 사운드를 가져온다.
	USoundCue* SoundCue = BGMDataRows[static_cast<int32>(BGM)]->SoundCue;
	if (!IsValid(SoundCue))
	{
		LOG(Error, TEXT("BGM Data Table에 정의된 SoundCue가 유효하지 않습니다."));
		return;
	}

	LOG(Warning, TEXT("BGM 재생"));
	
	// 기존 BGM 정지
	if (CurrentBGMAudioComponent && CurrentBGMAudioComponent->IsPlaying())
	{
		CurrentBGMAudioComponent->Stop();
	}

	// UGameplayStatics를 사용하여 BGM 재생
	CurrentBGMAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), SoundCue);
}

void USoundSubSystem::StopBGM()
{
	// 기존 BGM 정지
	if (CurrentBGMAudioComponent && CurrentBGMAudioComponent->IsPlaying())
	{
		CurrentBGMAudioComponent->Stop();
	}
}

