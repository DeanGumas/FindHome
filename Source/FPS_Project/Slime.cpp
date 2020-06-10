// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime.h"

// Sets default values
ASlime::ASlime()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	// Set the collision radius
	CollisionComponent->InitSphereRadius(15.0f);

	// Set the root component as the collision component
	RootComponent = CollisionComponent;

	// Set projectile movement constants
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 0.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	// Set initial slime state
	SlimeState = ESlimeState::Stance;
}

// Called when the game starts or when spawned
void ASlime::BeginPlay()
{
	Super::BeginPlay();

	// Create dynamic material for color changing
	auto Mesh = FindComponentByClass<USkeletalMeshComponent>();
	auto Material = Mesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	Mesh->SetMaterial(0, DynamicMaterial);

	// Get reference to player character
	Character = Cast<AFPS_Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void ASlime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get vector from slime to player character
	ToPlayer = Character->GetActorLocation() - GetActorLocation(); 

	if (SlimeState == ESlimeState::JumpSquat || SlimeState == ESlimeState::Jump)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%f, %f, %f"), ToPlayer.X, ToPlayer.Y, ToPlayer.Z));
	}

	// Determine new rotation based on player character location
	FRotator NewRotation = GetActorRotation();
	float Rotation = atan(ToPlayer.Y / ToPlayer.X) * 180 / PI;
	// If the vector has a negative X component, add 180 to compensate for coordinate system
	if (ToPlayer.X < 0)
	{
		Rotation += 180;
	}
	// Setting the new rotation
	NewRotation.Yaw = Rotation;
	SetActorRotation(NewRotation);

	if (Alive)
	{
		// Switch on the slime's state
		switch (SlimeState)
		{
		case ESlimeState::Stance:
			// Check if the slime is close enough to "see" the player and jump towards them
			if (fabs(ToPlayer.X) < 500 && fabs(ToPlayer.Y) < 500)
			{
				WaitFrames++;
				// If the frames have exceeded the wait time, begin the jump squat
				if (WaitFrames == WaitLength)
				{
					SlimeState = ESlimeState::JumpSquat;
					WaitFrames = 0;
				}
			}
			// Reset waiting counter when the player is out of range
			else
			{
				WaitFrames = 0;
			}
			break;
		case ESlimeState::Jump:

			break;
		case ESlimeState::JumpSquat:
			SquatFrames++;
			// Change to jumping state after the specified jump squat length
			if (SquatFrames == SquatLength)
			{
				SlimeState = ESlimeState::Jump;
				SquatFrames = 0;
			}
			break;
		}

		// Check if the slime is close enough to attack the player
		if (fabs(ToPlayer.X) < 30 && fabs(ToPlayer.Y) < 30 && fabs(ToPlayer.Z) < 60)
		{
			// If there were enough frames between the last attack, damage the player again and reset the counter
			if (DamageFrames == DamageLength)
			{
				Character->Damage(1);
				DamageFrames = 0;
			}
			DamageFrames++;
		}
		// Reset damage counter when the player is no longer in range
		else
		{
			DamageFrames = DamageLength;
		}
	}
	// If dead, darken the material until black then destroy the slime
	else
	{
		if (Brightness > 0)
		{
			Brightness -= 0.05;
			DynamicMaterial->SetScalarParameterValue(TEXT("Brightness"), Brightness);
		}
		else
		{
			Destroy();
		}
	}
}

// Function to damage slime by the amount specified, killing it if the health reaches 0
void ASlime::Damage(uint8 Amount)
{
	Health -= Amount;
	if (Health == 0)
	{
		Alive = false;
	}
}

// Function to make slime jump
void ASlime::Jump()
{

}

