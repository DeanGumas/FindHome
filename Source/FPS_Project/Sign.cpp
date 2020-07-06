// Fill out your copyright notice in the Description page of Project Settings.


#include "Sign.h"

// Sets default values
ASign::ASign()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASign::BeginPlay()
{
	Super::BeginPlay();
	
	// Get reference to player character
	Character = Cast<AFPS_Character>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Get reference to HUD
	HUD = Cast<AFPS_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// Get constant position of the sign
	Location = GetActorLocation();
}

// Called every frame
void ASign::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get vector to player and check if within range of the sign
	if (Character)
	{
		ToPlayer = Character->GetActorLocation() - Location;
		if (IsActive)
		{
			if (fabs(ToPlayer.X) > Range.X || fabs(ToPlayer.Y) > Range.Y || fabs(ToPlayer.Z) > Range.Z)
			{
				IsActive = false;
				HUD->StopDisplayText();
			}
		}
		else
		{
			if (!IsActive && fabs(ToPlayer.X) < Range.X && fabs(ToPlayer.Y) < Range.Y && fabs(ToPlayer.Z) < Range.Z)
			{
				IsActive = true;
				HUD->DisplayText(Message);
			}
		}
	}
}

