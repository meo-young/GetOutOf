#include "Item/InteractableItem.h"
#include "Character/Component/InteractionComponent.h"
#include "Components/BoxComponent.h"
#include "Core/GOOPlayerController.h"
#include "Define/DefineClass.h"
#include "GameFramework/Character.h"
#include "UI/InventoryWidget.h"

AInteractableItem::AInteractableItem()
{
	EventTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Event Trigger Box"));
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
}

void AInteractableItem::Interact_Implementation()
{
	IInteractable::Interact_Implementation();

	if (OnInteractionStartDelegate.IsBound())
	{
		OnInteractionStartDelegate.Broadcast();
	}

	AGOOPlayerController* PlayerController = Cast<AGOOPlayerController>(GetWorld()->GetFirstPlayerController());
	UInventoryWidget* InventoryWidget = PlayerController->GetInventoryWidget();
	InventoryWidget->UnLockSlot( EmotionType, SlotIndex);
}

void AInteractableItem::DisableCollision()
{
	EventTriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
