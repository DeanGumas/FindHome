// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FPS_Character.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"
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

	// Sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	// Projectile movement component
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	// Slime State enum
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	ESlimeState SlimeState;

	// Damages slime by the amount specified
	UFUNCTION()
	void Damage(uint8 Amount);

private:
	// Dynamic material of the slime used to change its color
	UMaterialInstanceDynamic* DynamicMaterial;

	// Reference to the main character
	FVector CharacterLocation;
	AFPS_Character* Character;

	// Health parameter
	uint8 Health = 100;

	// Brightness parameter
	float Brightness = 1.0;

	// If the slime has been killed
	bool Alive = true;
};
