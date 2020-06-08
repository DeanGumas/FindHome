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

	if (Character)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), Character->GetActorLocation().X));
	}

	if (!Alive)
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

