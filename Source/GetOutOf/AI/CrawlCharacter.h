#pragma once

#include "CoreMinimal.h"
#include "AI/StealthCharacter.h"
#include "CrawlCharacter.generated.h"

class ULevelSequence;

UCLASS()
class GETOUTOF_API ACrawlCharacter : public AStealthCharacter
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	virtual bool CheckAllConditions() override;
	/** 플레이어가 후레쉬를 키고 있는 상태인 지 확인하는 함수입니다. */
	bool IsPlayerFlashLightOn();

	/** 플레이어와의 거리가 일정 거리 이내인 지 확인하는 함수입니다. */
	bool IsAcceptanceDistance();

	void ShowFadeTransition();

	UFUNCTION()
	void DestroyAI();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Stat")
	int32 AcceptanceDistance = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Stat")
	ULevelSequence* FadeTransitionLevelSequence;
	
	
};
