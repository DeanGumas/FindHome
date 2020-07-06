// Fill out your copyright notice in the Description page of Project Settings.


#include "Gem.h"

// Sets default values
AGem::AGem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGem::BeginPlay()
{
	Super::BeginPlay();
	
	// Create dynamic material for color changing
	auto Mesh = FindComponentByClass<UStaticMeshComponent>();
	auto Material = Mesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	Mesh->SetMaterial(0, DynamicMaterial);

	// Get reference to player character
	Character = Cast<AFPS_Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void AGem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get vector from gem to player character
	if (Character)
	{
		ToPlayer = Character->GetActorLocation() - GetActorLocation();

		// Check if the character is within range to collect it
		if (fabs(ToPlayer.X) < Range.X && fabs(ToPlayer.Y) < Range.Y && fabs(ToPlayer.Z) < Range.Z)
		{
			Character->GetGem();
			Destroy();
		}
	}

	// Increase and decrease brightness as needed to make it appear like a beacon
	if (Increasing)
	{
		BrightnessCounter++;

		if (BrightnessCounter > MaxBrightness)
		{
			Increasing = false;
		}
	}
	else
	{
		BrightnessCounter--;

		if (BrightnessCounter == 0)
		{
			Increasing = true;
		}
	}

	// Update brightness and continue to rotate the gem
	DynamicMaterial->SetScalarParameterValue(TEXT("EmissiveStrength"), BrightnessCounter/100.0);
	AddActorLocalRotation(FQuat(FRotator(0, RotationSpeed, 0)), false, 0, ETeleportType::None);
}

