#include "LevelSequence/GOOLevelSequenceActor.h"
#include "GetOutOf.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"

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

	// 재생 전에 레벨 시퀀스 플레이어를 변수화 해야 종료 델리게이트에서 활용할 수 있다.
	ALevelSequenceActor* OutActor;
	LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), OutActor);

	// 종료 델리게이트에 함수를 바인딩한다.
	LevelSequencePlayer->OnFinished.AddDynamic(this, &ThisClass::OnSequenceEnded);
}

void AGOOLevelSequenceActor::PlayLevelSequence()
{
	if (OnSequenceStartedDelegate.IsBound())
	{
		OnSequenceStartedDelegate.Broadcast();
	}

	LevelSequencePlayer->Play();
}

void AGOOLevelSequenceActor::OnSequenceEnded()
{
	if (OnSequenceEndedDelegate.IsBound())
	{
		OnSequenceEndedDelegate.Broadcast();
	}
}
