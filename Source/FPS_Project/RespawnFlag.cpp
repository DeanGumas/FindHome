// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnFlag.h"
#include "FPS_Character.h"

// Sets default values
ARespawnFlag::ARespawnFlag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARespawnFlag::BeginPlay()
{
	Super::BeginPlay();

	// Create dynamic material for color changing
	auto Mesh = FindComponentByClass<UStaticMeshComponent>();
	auto Material = Mesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	Mesh->SetMaterial(0, DynamicMaterial);
	
	// Get reference to player character
	Character = Cast<AFPS_Character>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Get constant position of the respawn flag and offset by specified amount
	Location = GetActorLocation();
	Location.X += Offset.X;
	Location.Y += Offset.Y;
	Location.Z += Offset.Z;
}

// Called every frame
void ARespawnFlag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get vector to player and check if within range to change active respawn location
	if (Character)
	{
		ToPlayer = Character->GetActorLocation() - Location;
		if (!IsActive && fabs(ToPlayer.X) < Range.X && fabs(ToPlayer.Y) < Range.Y && fabs(ToPlayer.Z) < Range.Z)
		{
			SetActive();
			Character->SetRespawnLocation(this);
		}
	}
}

// Function to set the respawn flag as active
void ARespawnFlag::SetActive()
{
	IsActive = true;
	DynamicMaterial->SetScalarParameterValue(TEXT("IsActive"), 1.0f);
}

// Function to set the respawn flag as inactive
void ARespawnFlag::SetInactive()
{
	IsActive = false;
	DynamicMaterial->SetScalarParameterValue(TEXT("IsActive"), 0.0f);
}
