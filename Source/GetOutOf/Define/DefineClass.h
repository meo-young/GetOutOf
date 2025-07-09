#pragma once

#define SURFACE_CONCRETE	SurfaceType1
#define SURFACE_WATER		SurfaceType2
#define SURFACE_METAL		SurfaceType3
#define SURFACE_DIRT		SurfaceType4

#define ECC_INTERACTION		ECC_GameTraceChannel2

UENUM(BlueprintType)
enum class ESFX : uint8
{
	WaterFootStep = 0,
	DirtFootStep  = 1,
	ConcreteFootStep = 2,
	MetalFootStep = 3,
};