#pragma once

#include "CoreMinimal.h"
#include "Item/InteractableItem.h"
#include "MusicBox.generated.h"

UCLASS()
class GETOUTOF_API AMusicBox : public AInteractableItem
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	virtual void Interact_Implementation() override;
	
};
