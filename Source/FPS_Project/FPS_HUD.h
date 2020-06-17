// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FPS_Character.h"
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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Primary draw function for the HUD
	virtual void DrawHUD() override;

	// Function to start displaying sign text
	UFUNCTION()
	void DisplayText(FString Text);

	// Function to stop displaying sign text
	UFUNCTION()
	void StopDisplayText();

protected:

	// Crosshair drawn at center of the screen
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;

	// Heart drawn at top left
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* HeartTexture;

	// Gems drawn at bottom left
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* GemTexture;

	// Full gem drawn at bottom left
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* GemFullTexture;

	// Reference to main character
	AFPS_Character* Character;

	// Whether or not a sign is being displayed
	bool DisplaySign = false;

	// The text of the sign being displayed
	FString SignText;
};
