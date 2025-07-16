#include "Core/GOOPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "GetOutOf.h"
#include "UI/InventoryWidget.h"
#include "UI/PlayerHUDWidget.h"

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

void AGOOPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Player HUD 위젯 인스턴스 생성 및 뷰포트에 추가
	if (IsValid(PlayerHUDWidgetClass))
	{
		PlayerHUDWidgetInstance = CreateWidget<UPlayerHUDWidget>(GetWorld(), PlayerHUDWidgetClass);
		if (IsValid(PlayerHUDWidgetInstance))
		{
			if (!PlayerHUDWidgetInstance->IsInViewport())
			{
				LOG(Log,TEXT("PlayerHUDWidget 인스턴스 생성 성공"));
				PlayerHUDWidgetInstance->AddToViewport();	
			}
		}
	}

	// Inventory 위젯 인스턴스 생성 및 뷰포트에 추가
	if (IsValid(InventoryWidgetClass))
	{
		InventoryWidgetInstance = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
	}
}
