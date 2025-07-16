#include "SubSystem/DialogueSubsystem.h"
#include "GetOutOf.h"
#include "DataTable/DialogueDataTable.h"

UDialogueSubsystem::UDialogueSubsystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_HappinessDialogue(TEXT("/Game/_GetOutOf/DataTable/DT_HappinessDialogue"));
	if (DT_HappinessDialogue.Succeeded())
	{
		HappinessDialogueDataTable = DT_HappinessDialogue.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DenialDialogue(TEXT("/Game/_GetOutOf/DataTable/DT_DenialDialogue"));
	if (DT_DenialDialogue.Succeeded())
	{
		DenialDialogueDataTable = DT_DenialDialogue.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_AngerDialogue(TEXT("/Game/_GetOutOf/DataTable/DT_AngerDialogue"));
	if (DT_AngerDialogue.Succeeded())
	{
		AngerDialogueDataTable = DT_AngerDialogue.Object;
	}


	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BargainingDialogue(TEXT("/Game/_GetOutOf/DataTable/DT_BargainingDialogue"));
	if (DT_BargainingDialogue.Succeeded())
	{
		BargainingDialogueDataTable = DT_BargainingDialogue.Object;
	}
}

void UDialogueSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	HappinessDialogueDataTable->GetAllRows<FDialogueDataTable>(TEXT(""), HappinessDialogueDataRows);
	DenialDialogueDataTable->GetAllRows<FDialogueDataTable>(TEXT(""), DenialDialogueDataRows);
	AngerDialogueDataTable->GetAllRows<FDialogueDataTable>(TEXT(""), AngerDialogueDataRows);
	BargainingDialogueDataTable->GetAllRows<FDialogueDataTable>(TEXT(""), BargainingDialogueDataRows);
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
