#include "Core/TutorialPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "GetOutOf.h"
#include "UI/HorrorWidget.h"

void ATutorialPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(MappingContext, 0);
	}
	else
	{
		LOG(Warning, TEXT("EnhancedInputLocalPlayerSubsystem이 유효하지 않습니다"));
	}
}

void ATutorialPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(HorrorWidgetClass))
	{
		HorrorWidgetInstance = CreateWidget<UHorrorWidget>(GetWorld(), HorrorWidgetClass);
		if (IsValid(HorrorWidgetInstance))
		{
			if (!HorrorWidgetInstance->IsInViewport())
			{
				LOG(Log, TEXT("HorrorWidget 인스턴스 생성 성공"));
				HorrorWidgetInstance->AddToViewport();
			}
		}
	}
}
