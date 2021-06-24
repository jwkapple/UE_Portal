// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_PortalGameMode.h"
#include "UE_PortalHUD.h"
#include "UE_PortalCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE_PortalGameMode::AUE_PortalGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUE_PortalHUD::StaticClass();
}
