// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "BasicProjectile.h"
#include "FPS_Character.generated.h"

UENUM(BlueprintType)
enum class ECharState : uint8
{
	Standing,
	Running,
	Shooting,
	JumpSquat,
	Jump,
	RightShot,
	LeftShot
};

UCLASS()
class FPS_PROJECT_API AFPS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPS_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input for moving forward and backward
	UFUNCTION()
	void MoveForward(float Value);

	// Handles input for moving left and right
	UFUNCTION()
	void MoveRight(float Value);

	// Sets jump flag when key pressed
	UFUNCTION()
	void StartJump();

	// Clears jump flag when key released
	UFUNCTION()
	void StopJump();

	// FPS Camera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPS_CameraComponent;

	// Shoot basic projectile
	UFUNCTION()
	void Shoot();

	// Start shooting projectiles
	UFUNCTION()
	void StartShooting();

	// Stop shooting projectiles
	UFUNCTION()
	void StopShooting();

	// Launch location for projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// Launch offset of dual wielded guns
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 DualWieldOffset;

	// Number of frames between projectiles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 ShootFrequency = 30;

	// Projectile class to spawn when shooting
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABasicProjectile> ProjectileClass;

	// Character State enum
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	ECharState CharacterState;

	// Character Health Value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	uint8 Health = 3;

	// FPS mesh visible only to player
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

private:
	// If the player jump has peaked
	bool Peaked = false;

	// If the player is still shooting projectiles
	bool StillShooting = false;

	// Number of shooting frames active
	uint8 ShootFrames = 0;

	// Number of squat frames active
	uint8 SquatFrames = 0;

	// Whether the last shot was with the left or right gun
	bool RightShot = false;
};
  