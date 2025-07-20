#include "Item/Balloon.h"
#include "GetOutOf.h"

ABalloon::ABalloon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABalloon::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = FVector(6126.0f, -1635.0f, 200.0f);
}

void ABalloon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FloatUp(DeltaSeconds);
}

void ABalloon::Interact_Implementation()
{
	Super::Interact_Implementation();
}

void ABalloon::FloatUp(const float DeltaSeconds)
{
	// 시간 누적용 변수
	ElapsedTime += DeltaSeconds;

	// Sine 곡선을 이용한 부드러운 위아래 이동
	const float OffsetZ = FMath::Sin((ElapsedTime / Period) * PI * 2.0f) * Amplitude;

	FVector NewLocation = InitialLocation;
	NewLocation.Z += OffsetZ;

	SetActorLocation(NewLocation);
}
