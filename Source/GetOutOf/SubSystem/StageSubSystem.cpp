#include "SubSystem/StageSubSystem.h"
#include "GetOutOf.h"

void UStageSubSystem::StartStage()
{
	if (OnStageStartedDelegate.IsBound())
	{
		LOG(Log, TEXT("스테이지 시작"));
		OnStageStartedDelegate.Broadcast();
	}
}

void UStageSubSystem::EndStage()
{
	if (OnStageEndedDelegate.IsBound())
	{
		LOG(Log, TEXT("스테이지 종료"));
		OnStageEndedDelegate.Broadcast();
	}
}
