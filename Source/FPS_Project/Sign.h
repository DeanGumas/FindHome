// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPS_Character.h"
#include "FPS_HUD.h"
#include "Sign.generated.h"

UCLASS()
class FPS_PROJECT_API ASign : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASign();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Range in each direction for distance to player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector Range;

	// Message to display with the sign
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FString Message;

	// Location of the sign
	FVector Location;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Vector directed from the flag to the player character
	FVector ToPlayer;

	// Reference to player character
	AFPS_Character* Character;

	// Reference to HUD for updating the screen
	AFPS_HUD* HUD;

	// If the sign is currently displaying on the characters screen
	bool IsActive = false;
};
