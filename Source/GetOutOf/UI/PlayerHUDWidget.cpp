#include "UI/PlayerHUDWidget.h"
#include "TimerWidget.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TimerWidget->ActivateTimerText();
}
