#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTable/DialogueDataTable.h"
#include "SlotWidget.generated.h"

class UButton;
class UTextBlock;
struct FDialogueDataTable;

UCLASS()
class GETOUTOF_API USlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** 슬롯의 투명도를 변경하는 함수
	 * 
	 * 활성화 - 0.15f
	 * 비활성화 - 0.0f
	 */
	UFUNCTION(BlueprintCallable)
	void SetOpacity(float Opacity);

	void SetTitleText(const FString& NewTitle);


private:
	/** 제목 텍스트 블록 */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TitleText;
	
	/** 슬롯 버튼 */
	UPROPERTY(meta = (BindWidget))
	UButton* SlotButton;

	/** 현재 슬롯에 저장된 대화 데이터 */
	FDialogueDataTable* DialogueData;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetTitle() const { return DialogueData->TitleText; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetDialogue() const { return DialogueData->DialogueText.ToString(); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTexture2D* GetImage() const { return DialogueData->DialogueImage; }

	FORCEINLINE FDialogueDataTable* GetDialogueData() const { return DialogueData; }
	FORCEINLINE void SetDialogueData(FDialogueDataTable* NewDialogueData) { DialogueData = NewDialogueData; }
	
};
