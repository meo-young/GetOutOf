#include "AnimNotify/AnimNotify_FootStep.h"
#include "GetOutOf.h"
#include "Define/DefineClass.h"

void UAnimNotify_FootStep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	// Notify를 호출한 메시의 소유자를 가져온다.
	const AActor* Owner = MeshComp->GetOwner();
	if (!IsValid(Owner)) return;

	const UWorld* World = Owner->GetWorld();
	if (!IsValid(World)) return;

	// PhysicalMaterial을 가져오기 위한 쿼리 파라미터를 설정한다.
	QueryParams.bReturnPhysicalMaterial = true;
	
	// 액터의 -150.0f 아래 위치를 계산한다.
	const FVector Location = Owner->GetActorLocation();
	const FVector DownVector = Owner->GetActorUpVector() * -200.0f;
	const FVector Direction = Location + DownVector;

	// LineTrace 실시한다.
	const bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		Location,
		Direction,
		ECC_Visibility,
		QueryParams
		);

#if WITH_EDITOR
	DrawDebugLine(World, Location, Direction, FColor::Red, false, 3.0f, 0, 1.0f);
#endif
	
	// Surface Type에 따른 발걸음 소리를 재생한다.
	if (bHit)
	{
		if (HitResult.PhysMaterial.IsValid())
		{
			switch (HitResult.PhysMaterial->SurfaceType)
			{
			case SURFACE_CONCRETE:
				LOG(Warning, TEXT("Surface Type: Default"));
				break;
			case SURFACE_WATER:
				LOG(Warning, TEXT("Surface Type: 1"));
				break;
			case SURFACE_METAL:
				LOG(Warning, TEXT("Surface Type: 2"));
				break;
			case SURFACE_DIRT:
				LOG(Warning, TEXT("Surface Type: 3"));
				break;
			default:
				LOG(Warning, TEXT("Surface Type: Unknown"));
				break;
			}
		}
	}
}
