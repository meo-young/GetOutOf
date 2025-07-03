#include "Core/GOOPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "GetOutOf.h"

void AGOOPlayerController::SetupInputComponent()
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
