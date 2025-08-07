#include "Core/ProloguePlayerController.h"
#include "GetOutOf.h"
#include "UI/DialogueWidget.h"

void AProloguePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	LOG(Warning, TEXT(" Begin"));

	// Dialogue 위젯 인스턴스 생성 및 뷰포트에 추가
	if (IsValid(DialogueWidgetClass))
	{
		DialogueWidgetInstance = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
		if (!DialogueWidgetInstance->IsInViewport())
		{
			DialogueWidgetInstance->AddToViewport();
		}
	}
}
