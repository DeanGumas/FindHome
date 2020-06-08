// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FPS_Project.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "FPS_HUD.generated.h"

/**
 * 
 */
UCLASS()
class FPS_PROJECT_API AFPS_HUD : public AHUD
{
	GENERATED_BODY()

public:
	// Primary draw function for the HUD
	virtual void DrawHUD() override;

protected:

	// Crosshair drawn at center of the screen
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;

	// Heart drawn at top left
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* HeartTexture;
};
