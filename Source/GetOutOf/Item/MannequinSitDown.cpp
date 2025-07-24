#include "Item/MannequinSitDown.h"
#include "GameFramework/Character.h"

AMannequinSitDown::AMannequinSitDown()
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
}

void AMannequinSitDown::BeginPlay()
{
	Super::BeginPlay();
}

void AMannequinSitDown::Interact_Implementation()
{
	Super::Interact_Implementation();
}
