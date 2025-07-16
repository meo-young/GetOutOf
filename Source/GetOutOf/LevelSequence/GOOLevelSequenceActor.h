#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceActor.h"
#include "Interface/Interactable.h"
#include "GOOLevelSequenceActor.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSequenceStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSequenceEnded);

class ULevelSequence;

UCLASS()
class GETOUTOF_API AGOOLevelSequenceActor : public ALevelSequenceActor, public IInteractable
{
	GENERATED_BODY()

public:
	AGOOLevelSequenceActor(const FObjectInitializer& Init);
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
public:
	/** LevelSequence에 Interact가 시작될 때 호출되는 델리게이트 */
	UPROPERTY(BlueprintAssignable)
	FOnInteractionStart OnInteractionStartDelegate;
	
	/** LevelSequence가 시작될 때 호출되는 델리게이트 */
	UPROPERTY(BlueprintAssignable)
	FOnSequenceStarted OnSequenceStartedDelegate;

	/** LevelSequence가 종료될 때 호출되는 델리게이트 */
	UPROPERTY(BlueprintAssignable)
	FOnSequenceEnded OnSequenceEndedDelegate;
	
public:
	/** 등록된 LevelSequence를 재생하는 함수 */
	UFUNCTION(BlueprintCallable)
	void PlayLevelSequence();
	
	/** 등록된 LevelSequence를 루프로 재생하는 함수 */
	UFUNCTION(BlueprintCallable)
	void PlayLevelSequenceForLoop();

	/** 등록된 LevelSequence를 루프로 재생하는 함수 */
	UFUNCTION(BlueprintCallable)
	void StopLevelSequence();
	
	/** LevelSequence의 종료 델리게이트에 바인딩할 함수 */
	UFUNCTION(BlueprintCallable)
	void OnSequenceEnded();

	/** Interactable 인터페이스의 Interact 함수 구현 */
	virtual void Interact_Implementation() override;

private:
	UFUNCTION()
	void DisableCollision();

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	uint8 EmotionType = 0;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	uint8 SlotIndex = 0;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<ULevelSequence> LevelSequence = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<ULevelSequencePlayer> LevelSequencePlayer = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	UBoxComponent* EventTriggerBox = nullptr;
	
};
