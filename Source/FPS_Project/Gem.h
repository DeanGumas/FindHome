// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInterface.h"
#include "FPS_Character.h"
#include "Gem.generated.h"

UCLASS()
class FPS_PROJECT_API AGem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Max brightness of the gem
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	int MaxBrightness;

	// Rotation speed of the gem
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	float RotationSpeed;

	// Range for the character to obtain the gem
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector Range;

private:
	// Dynamic material used to change color
	UMaterialInstanceDynamic* DynamicMaterial;

	// Frame counter for determining emissive brightness
	int BrightnessCounter = 0;

	// Whether the brightness is increasing or decreasing
	bool Increasing = true;

	// Current rotation of the gem
	float CurrentRotation = 0.0f;

	// Vector directed from the gem to the player character
	FVector ToPlayer;

	// Reference to player character
	AFPS_Character* Character;
};
