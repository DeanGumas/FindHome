// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/MovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "FPS_Character.h"
#include "Slime.generated.h"

class AFPS_Character;

UENUM(BlueprintType)
enum class ESlimeState : uint8
{
	Stance,
	JumpSquat,
	Jump
};

UCLASS()
class FPS_PROJECT_API ASlime : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlime();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Overridden reset function
	virtual void Reset() override;

	// Sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	// Projectile movement component
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	// Slime State enum
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	ESlimeState SlimeState;

	// Number of frames to stay in jump squat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 SquatLength;

	// Number of frames to wait before jumping towards the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 WaitLength;

	// Number of frames between damages to the player when within range
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 DamageLength;

	// Damages slime by the amount specified
	UFUNCTION()
	void Damage(uint8 Amount);

	// Makes slime jump
	UFUNCTION()
	void Jump();

private:
	// Dynamic material of the slime used to change its color
	UMaterialInstanceDynamic* DynamicMaterial;

	// Reference to the main character
	AFPS_Character* Character;

	// Health parameter
	uint8 Health = 100;

	// Brightness parameter
	float Brightness = 1.0;

	// If the slime has been killed
	bool Alive = true;

	// Frames the slime has been in jump squat
	uint8 SquatFrames = 0;

	// Frames the slime has been waiting to move
	uint8 WaitFrames = 0;

	// Frames the slime has been waiting to damage the player
	uint8 DamageFrames = DamageLength;

	// Vector directed from the slime to the player character
	FVector ToPlayer;

	// Starting location of the slime
	FVector StartLocation;
};
