#include "Item/InteractableItem.h"
#include "Character/Component/InteractionComponent.h"
#include "Components/BoxComponent.h"
#include "Core/GOOPlayerController.h"
#include "Define/DefineClass.h"
#include "GameFramework/Character.h"
#include "SubSystem/StageSubSystem.h"
#include "UI/InventoryWidget.h"

AInteractableItem::AInteractableItem()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));
	SceneComponent->SetupAttachment(RootComponent);
	
	EventTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Event Trigger Box"));
	EventTriggerBox->SetupAttachment(SceneComponent);
	EventTriggerBox->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	EventTriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	EventTriggerBox->SetCollisionResponseToChannel(ECC_INTERACTION, ECR_Block);
}

void AInteractableItem::BeginPlay()
{
	Super::BeginPlay();

	if (UInteractionComponent* InteractionComponent = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UInteractionComponent>())
	{
		InteractionComponent->OnInteractionEndedDelegate.AddDynamic(this, &ThisClass::DisableCollision);
	}

	if (UStageSubSystem* StageSubsystem = GetGameInstance()->GetSubsystem<UStageSubSystem>())
	{
		StageSubsystem->OnStageEndedDelegate.AddDynamic(this, &ThisClass::DestroyItem);
	}
}

void AInteractableItem::Interact_Implementation()
{
	IInteractable::Interact_Implementation();

	if (OnInteractionStartDelegate.IsBound())
	{
		OnInteractionStartDelegate.Broadcast();
	}

	/*if (AGOOPlayerController* PlayerController = Cast<AGOOPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (UInventoryWidget* InventoryWidget = PlayerController->GetInventoryWidget())
		{
			InventoryWidget->UnLockSlot( EmotionType, SlotIndex);
		}
	}*/
}

void AInteractableItem::DisableCollision()
{
	if (IsValid(EventTriggerBox))
	{
		EventTriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AInteractableItem::DestroyItem()
{
	if (IsValid(this))
	{
		Destroy();
	}
}
