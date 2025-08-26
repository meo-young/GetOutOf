#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DialogueSubsystem.generated.h"

struct FDialogueDataTable;

UCLASS()
class GETOUTOF_API UDialogueSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	/** Dialogue 데이터 테이블에서 특정 ID에 해당하는 대화를 가져오는 함수 */
	FDialogueDataTable* GetDialogueByID(uint8 EmotionID, uint8 SlotID);

private:
	/** HappinessDialogue 데이터 테이블 */
	UPROPERTY()
	UDataTable* HappinessDialogueDataTable;

	/** HappinessDialogue 데이터 테이블에서 추출한 모든 행 */
	TArray<FDialogueDataTable*> HappinessDialogueDataRows;

	/** DenialDialogue 데이터 테이블 */
	UPROPERTY()
	UDataTable* DenialDialogueDataTable;

	/** DenialDialogue 데이터 테이블에서 추출한 모든 행 */
	TArray<FDialogueDataTable*> DenialDialogueDataRows;

	/** AngerDialogue 데이터 테이블 */
	UPROPERTY()
	UDataTable* AngerDialogueDataTable;

	/** AngerDialogue 데이터 테이블에서 추출한 모든 행 */
	TArray<FDialogueDataTable*> AngerDialogueDataRows;

	/** BargainingDialogue 데이터 테이블 */
	UPROPERTY()
	UDataTable* BargainingDialogueDataTable;

	/** BargainingDialogue 데이터 테이블에서 추출한 모든 행 */
	TArray<FDialogueDataTable*> BargainingDialogueDataRows;
	
};
