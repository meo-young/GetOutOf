#include "LevelSequence/GOOLevelSequenceActor.h"
#include "GetOutOf.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "Character/GOOCharacter.h"
#include "Components/BoxComponent.h"
#include "Character/Component/InteractionComponent.h"
#include "Core/GOOPlayerController.h"
#include "Define/DefineClass.h"
#include "GameFramework/Character.h"
#include "SubSystem/StageSubSystem.h"
#include "UI/InventoryWidget.h"

AGOOLevelSequenceActor::AGOOLevelSequenceActor(const FObjectInitializer& Init) : Super(Init)
{
	
}

void AGOOLevelSequenceActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// 등록된 레벨 시퀀스를 추출한다.
	LevelSequence = GetSequence();
	if (!IsValid(LevelSequence))
	{
		LOG(Error, TEXT("LevelSequence Is Not Valid !"));
		return;
	}

	if (LevelSequencePlayer) return;

	// 재생 전에 레벨 시퀀스 플레이어를 변수화 해야 종료 델리게이트에서 활용할 수 있다.
	ALevelSequenceActor* OutActor;
	LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), OutActor);
}

void AGOOLevelSequenceActor::BeginPlay()
{
	Super::BeginPlay();

	// 종료 델리게이트에 함수를 바인딩한다.
	LevelSequencePlayer->OnFinished.AddDynamic(this, &ThisClass::OnSequenceEnded);

	LOG(Warning, TEXT("%s BeginPlay"), *GetName());
}

void AGOOLevelSequenceActor::PlayLevelSequence()
{
	LOG(Warning, TEXT("%s PlayLevelSequence"), *GetName());
	if (OnSequenceStartedDelegate.IsBound())
	{
		OnSequenceStartedDelegate.Broadcast();
	}

	LevelSequencePlayer->Play();
}

void AGOOLevelSequenceActor::PlayLevelSequenceForLoop()
{
	if (OnSequenceStartedDelegate.IsBound())
	{
		OnSequenceStartedDelegate.Broadcast();
	}

	LevelSequencePlayer->PlayLooping();
}

void AGOOLevelSequenceActor::StopLevelSequence()
{
	LevelSequencePlayer->Stop();
}

void AGOOLevelSequenceActor::OnSequenceEnded()
{
	if (OnSequenceEndedDelegate.IsBound())
	{
		OnSequenceEndedDelegate.Broadcast();
	}
}
