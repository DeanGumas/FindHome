// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInterface.h"
#include "RespawnFlag.generated.h"

class AFPS_Character;

UCLASS()
class FPS_PROJECT_API ARespawnFlag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARespawnFlag();

	// Range in each direction for distance to player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector Range;

	// Offset by which to set player respawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector Offset;

	// Function to set the respawn flag as active
	UFUNCTION()
	void SetActive();

	// Function to set the respawn flag as inactive
	UFUNCTION()
	void SetInactive();

	// Respawn location of the respawn flag
	FVector Location;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Dynamic material used to change color
	UMaterialInstanceDynamic* DynamicMaterial;

	// Whether or not this is the active respawn flag
	bool IsActive = false;

	// Vector directed from the flag to the player character
	FVector ToPlayer;

	// Reference to player character
	AFPS_Character* Character;
};
