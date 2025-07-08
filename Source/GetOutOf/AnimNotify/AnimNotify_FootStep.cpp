#include "AnimNotify/AnimNotify_FootStep.h"
#include "GetOutOf.h"
#include "Define/DefineClass.h"
#include "Sound/SoundSubSystem.h"

void UAnimNotify_FootStep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	// Notify를 호출한 메시의 소유자를 가져온다.
	const AActor* Owner = MeshComp->GetOwner();
	if (!IsValid(Owner)) return;

	const UWorld* World = Owner->GetWorld();
	if (!IsValid(World)) return;

	UGameInstance* GameInstance = World->GetGameInstance();
	if (!IsValid(GameInstance)) return;
	
	USoundSubSystem* SoundSubSystem = GameInstance->GetSubsystem<USoundSubSystem>();
	if (!IsValid(SoundSubSystem)) return;

	// PhysicalMaterial을 가져오기 위한 쿼리 파라미터를 설정한다.
	QueryParams.bReturnPhysicalMaterial = true;
	
	// 액터의 -150.0f 아래 위치를 계산한다.
	const FVector CurrentLocation = Owner->GetActorLocation();
	const FVector DownVector = Owner->GetActorUpVector() * -200.0f;
	const FVector TargetLocation = CurrentLocation + DownVector;
	const FRotator Rotator = Owner->GetActorRotation();

	// LineTrace 실시한다.
	const bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		CurrentLocation,
		TargetLocation,
		ECC_Visibility,
		QueryParams
		);

#if WITH_EDITOR
	DrawDebugLine(World, CurrentLocation, TargetLocation, FColor::Red, false, 3.0f, 0, 1.0f);
#endif
	
	// Surface Type에 따른 발걸음 소리를 재생한다.
	if (bHit)
	{
		LOG(Warning, TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName());
		if (HitResult.PhysMaterial.IsValid())
		{
			switch (HitResult.PhysMaterial->SurfaceType)
			{
			case SURFACE_CONCRETE:
				LOG(Warning, TEXT("Concrete Foot Step"));
				SoundSubSystem->PlaySFX(ESFX::ConcreteFootStep, TargetLocation, Rotator);
				break;
			case SURFACE_WATER:
				LOG(Warning, TEXT("Water Foot Step"));
				SoundSubSystem->PlaySFX(ESFX::WaterFootStep, TargetLocation, Rotator);
				break;
			case SURFACE_METAL:
				LOG(Warning, TEXT("Metal Foot Step"));
				SoundSubSystem->PlaySFX(ESFX::MetalFootStep, TargetLocation, Rotator);
				break;
			case SURFACE_DIRT:
				LOG( Warning, TEXT("Dirt Foot Step"));
				SoundSubSystem->PlaySFX(ESFX::DirtFootStep, TargetLocation, Rotator);
				break;
			default:
				LOG( Warning, TEXT("Default Foot Step"));
				SoundSubSystem->PlaySFX(ESFX::ConcreteFootStep, TargetLocation, Rotator);
				break;
			}
		}
	}
}
