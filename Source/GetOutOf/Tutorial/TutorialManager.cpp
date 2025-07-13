#include "Tutorial/TutorialManager.h"
#include "GetOutOf.h"

ATutorialManager::ATutorialManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATutorialManager::BeginPlay()
{
	Super::BeginPlay();

	WASDTutorial.TutorialCondition.BindUObject(this, &ThisClass::WASDTutorialCondition);
	SprintTutorial.TutorialCondition.BindUObject(this, &ATutorialManager::SprintTutorialCondition);
	PictureTutorial.TutorialCondition.BindUObject(this, &ThisClass::PictureTutorialCondition);
	
	TutorialEventList.Emplace(WASDTutorial);
	TutorialEventList.Emplace(SprintTutorial);
	TutorialEventList.Emplace(PictureTutorial);
}

void ATutorialManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsTutorialActive)
	{
		if (TutorialEventList[0].TutorialCondition.Execute())
		{
			NextTutorial();
		}
	}
}

void ATutorialManager::StartTutorial()
{
	if (!TutorialEventList.IsEmpty())
	{
		if (TutorialEventList[0].TutorialStartDelegate.IsBound())
		{
			LOG(Warning, TEXT("튜토리얼 조건을 만족합니다."));
			bIsTutorialActive = true;
			TutorialEventList[0].TutorialStartDelegate.Broadcast();
		}
	}
	else
	{
		LOG(Warning, TEXT("튜토리얼이 모두 끝났습니다"));
		if (OnAllTutorialEndDelegate.IsBound())
		{
			OnAllTutorialEndDelegate.Broadcast();
		}
		SetActorTickEnabled(false);
	}
}

void ATutorialManager::NextTutorial()
{
	LOG(Warning, TEXT("튜토리얼이 완료되었습니다. 다음 튜토리얼로 넘어갑니다."));
	bIsTutorialActive = false;
	
	GetWorldTimerManager().SetTimer(TutorialHandle, this, &ThisClass::RemoveTutorial, 1.0f, false);
}

void ATutorialManager::RemoveTutorial()
{
	LOG(Warning, TEXT("튜토리얼을 제거합니다."));
	
	if (TutorialEventList[0].TutorialEndDelegate.IsBound())
	{
		TutorialEventList[0].TutorialEndDelegate.Broadcast();
	}

	TutorialEventList.RemoveAt(0);

	GetWorldTimerManager().SetTimer(TutorialHandle, this, &ThisClass::StartTutorial, 3.0f, false);
}

bool ATutorialManager::WASDTutorialCondition()
{
	bool bWDown = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::W);
	bool bADown = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::A);
	bool bSDown = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::S);
	bool bDDown = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::D);

	return bWDown || bADown || bSDown || bDDown; 
}

bool ATutorialManager::SprintTutorialCondition()
{
	bool bShiftDown = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::LeftShift);

	return bShiftDown;
}

bool ATutorialManager::PictureTutorialCondition()
{
	bool bPictureInputDown = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::LeftMouseButton);

	return bPictureInputDown;
}

