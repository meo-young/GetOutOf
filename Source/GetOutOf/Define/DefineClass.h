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
	CameraBeep = 4,
	CameraFlash = 5,
	SwitchOn = 6,
	SwitchOff = 7
};

UENUM(BlueprintType)
enum class EBGM : uint8
{
	HorrorBGM = 0,
	LightHorrorBGM = 1
};

UENUM(BlueprintType)
enum class EVoiceType : uint8
{
	PlayABit = 0,
	WTF = 1,
	MusicBox = 2,
	Donald = 3,
	Jesus = 4,
	SameThing = 5
};