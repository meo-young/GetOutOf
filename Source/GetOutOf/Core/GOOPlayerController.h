#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GOOPlayerController.generated.h"

class UInventoryWidget;
class UPlayerHUDWidget;
class UInputMappingContext;

UCLASS()
class GETOUTOF_API AGOOPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* MappingContext = nullptr;

	/** Player HUD 위젯 클래스 */
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UPlayerHUDWidget> PlayerHUDWidgetClass;

	/** Player HUD 위젯 인스턴스 */
	UPROPERTY()
	UPlayerHUDWidget* PlayerHUDWidgetInstance;

	/** Player HUD 위젯 클래스 */
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	/** Player HUD 위젯 인스턴스 */
	UPROPERTY()
	UInventoryWidget* InventoryWidgetInstance;


public:
	FORCEINLINE UPlayerHUDWidget* GetPlayerHUDWidget() const { return PlayerHUDWidgetInstance; }
	FORCEINLINE UInventoryWidget* GetInventoryWidget() const { return InventoryWidgetInstance; }

};
