#include "SubSystem/DialogueSubsystem.h"
#include "GetOutOf.h"
#include "DataTable/DialogueDataTable.h"

void UDialogueSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

FDialogueDataTable* UDialogueSubsystem::GetDialogueByID(uint8 EmotionID, uint8 SlotID)
{
	switch (EmotionID)
	{
	case 0:
		return HappinessDialogueDataRows[SlotID];
	case 1:
		return DenialDialogueDataRows[SlotID];
	case 2:
		return AngerDialogueDataRows[SlotID];
	case 3:
		return BargainingDialogueDataRows[SlotID];
	default:
		return nullptr;
	}
}
