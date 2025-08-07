#include "AnimNotify/AnimNotify_SFX.h"
#include "SubSystem/SoundSubSystem.h"

void UAnimNotify_SFX::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                             const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp->GetOwner()) return;

	// 액터의 현재 위치를 구합니다.
	const FVector CurrentLocation = MeshComp->GetOwner()->GetActorLocation();

	UWorld* World = MeshComp->GetOwner()->GetWorld();
	if (!World) return;
	
	UGameInstance* GameInstance = World->GetGameInstance();
	if (!GameInstance) return;

	// 현재 위치를 기준으로 SFX를 재생합니다.
	if (USoundSubSystem* SoundSubsystem = GameInstance->GetSubsystem<USoundSubSystem>())
	{
		SoundSubsystem->PlaySFX(SFX, CurrentLocation, FRotator(0, 0, 0));	
	}
	
}
