// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Slime.h"
#include "BreakableBlock.h"
#include "MovableBlock.h"
#include "FreezableBlock.h"
#include "BasicProjectile.generated.h"

UCLASS()
class FPS_PROJECT_API ABasicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicProjectile();

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

	// Amount of damage the projectile deals
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	uint8 Damage = 25;

	// Function to initialize projectile velocity in shooting direction
	UFUNCTION()
	void ShootInDirection(const FVector& ShootDirection);

	// Function to handle collision
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
