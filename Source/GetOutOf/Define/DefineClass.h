#pragma once

#define SURFACE_CONCRETE	SurfaceType1
#define SURFACE_WATER		SurfaceType2
#define SURFACE_METAL		SurfaceType3
#define SURFACE_DIRT		SurfaceType4

#define ECC_INTERACTION		ECC_GameTraceChannel2
#define ECC_DOOR			ECC_GameTraceChannel3

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
	SwitchOff = 7,
	DiaryOpen = 8,
	Mannequin_FootStep = 9,
	UnlockDoor = 10
};

UENUM(BlueprintType)
enum class EBGM : uint8
{
	HorrorBGM = 0,
	LightHorrorBGM = 1,
	CrawlMannequinBGM = 2
};

UENUM(BlueprintType)
enum class EVoiceType : uint8
{
	PlayABit = 0,
	WTF = 1,
	MusicBox = 2,
	Donald = 3,
	Jesus = 4,
	SameThing = 5,
	WhereAreYou = 6,
	HoldOn = 7,
	TooDark = 8,
	FindMe = 9,
	RedLight = 10,
	GreenLight = 11,
	LetsPlay = 12,
	BeingWith = 13
};