// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FPS_Project.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "FPS_HUD.generated.h"

class AFPS_Character;

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

	// Function to start displaying sign prompt text
	UFUNCTION()
	void DisplayText(FText Text);

	// Function to stop displaying sign prompt text
	UFUNCTION()
	void StopDisplayText();

	// Function to draw sign message
	UFUNCTION()
	void DrawSignMessage();

	// Function to stop drawing sign message
	UFUNCTION()
	void StopDrawSignMessage();

	// Sign TextBox size
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	FVector2D SignTextBoxSize;

	// The text of the sign being displayed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (MultiLine = true))
	FText SignText;

	// Whether or not a sign is being displayed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	bool DisplaySign = false;

	// Whether the player is within range to read a sign
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	bool WithinSignRange = false;

protected:

	// Crosshair drawn at center of the screen
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;

	// Heart drawn at top left
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* HeartTexture;

	// Gems drawn at top left
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* GemTexture;

	// Full gem drawn at top left
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* GemFullTexture;

	// Sign background to be drawn on screen
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* SignBackgroundTexture;

private:
	// Reference to main character
	AFPS_Character* Character;

	// Center of canvas
	FVector2D Center;

	// Text size in the X Dimension
	float XSize;

	// Text size in the Y Dimension
	float YSize;
};
