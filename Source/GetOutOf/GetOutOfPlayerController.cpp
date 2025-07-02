// Copyright Epic Games, Inc. All Rights Reserved.


#include "GetOutOfPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "GetOutOfCameraManager.h"

AGetOutOfPlayerController::AGetOutOfPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AGetOutOfCameraManager::StaticClass();
}

void AGetOutOfPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
