#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GOOGameInstance.generated.h"

UCLASS()
class GETOUTOF_API UGOOGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
};
