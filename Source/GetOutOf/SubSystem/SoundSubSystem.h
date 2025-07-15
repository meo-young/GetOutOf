#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SoundSubSystem.generated.h"

struct FSFXDataTable;
struct FBGMDataTable;
enum class ESFX : uint8;
enum class EBGM : uint8;

UCLASS()
class GETOUTOF_API USoundSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USoundSubSystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	/** PlayAtLocation으로 사운드를 재생한다. */
	void PlaySFX(ESFX SFX, const FVector& InLocation, const FRotator& InRotator);

	/** Loop로 BGM을 재생한다. */
	void PlayBGM(EBGM BGM);

	/** 현재 재생중인 BGM을 중단한다. */
	void StopBGM();

private:
	/** SFX 데이터 테이블 */
	UPROPERTY()
	TObjectPtr<UDataTable> SFXDataTable;

	/** SFX 데이터 테이블에서 추출한 모든 행 */
	TArray<FSFXDataTable*> SFXDataRows;

	/** BGM 데이터 테이블 */
	UPROPERTY()
	TObjectPtr<UDataTable> BGMDataTable;

	/** BGM 데이터 테이블에서 추출한 모든 행 */
	TArray<FBGMDataTable*> BGMDataRows;

	UPROPERTY()
	UAudioComponent* CurrentBGMAudioComponent;
};
