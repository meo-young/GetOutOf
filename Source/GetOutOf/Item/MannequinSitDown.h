#pragma once

#include "CoreMinimal.h"
#include "Item/InteractableItem.h"
#include "MannequinSitDown.generated.h"

UCLASS()
class GETOUTOF_API AMannequinSitDown : public AInteractableItem
{
	GENERATED_BODY()

public:
	AMannequinSitDown();
	virtual void BeginPlay() override;

public:
	virtual void Interact_Implementation() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* SkeletalMesh;
	
};
