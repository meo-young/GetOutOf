#include "Sound/SoundSubSystem.h"
#include "GetOutOf.h"
#include "DataTable/SFXDataTable.h"
#include "Define/DefineClass.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

USoundSubSystem::USoundSubSystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SFX(TEXT("/Game/_GetOutOf/DataTable/DT_SFX"));
	if (DT_SFX.Succeeded())
	{
		SFXDataTable = DT_SFX.Object;
	}
}

void USoundSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// SFXDataTable의 모든 데이터를 추출한다.
	SFXDataTable->GetAllRows<FSFXDataTable>(TEXT(""), SFXDataRows);
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

