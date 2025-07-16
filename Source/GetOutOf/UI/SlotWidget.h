#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotWidget.generated.h"

class UTextBlock;

UCLASS()
class GETOUTOF_API USlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** 일기 제목을 설정하는 함수 */
	UFUNCTION(BlueprintCallable)
	void SetTitleText(const FString& Title);

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TitleText;
	
};
