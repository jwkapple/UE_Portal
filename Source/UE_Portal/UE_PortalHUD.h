// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UE_PortalHUD.generated.h"

UCLASS()
class AUE_PortalHUD : public AHUD
{
	GENERATED_BODY()

public:
	AUE_PortalHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

