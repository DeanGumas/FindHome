// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicProjectile.h"

// Sets default values
ABasicProjectile::ABasicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	// Set collision profile
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABasicProjectile::OnHit);

	// Set the collision radius
	CollisionComponent->InitSphereRadius(20.0f);

	// Set the root component as the collision component
	RootComponent = CollisionComponent;

	// Set projectile movement constants
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
}

// Called when the game starts or when spawned
void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Set lifespan
	SetLifeSpan(3);
}

// Called every frame
void ABasicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Function that initializes the projectile's velocity in the shoot direction
void ABasicProjectile::ShootInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// Function to handle collision
void ABasicProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Check if the projectile hit a slime
	ASlime* Slime = Cast<ASlime>(OtherActor);
	ABreakableBlock* BreakableBlock = Cast<ABreakableBlock>(OtherActor);
	AMovableBlock* MovableBlock = Cast<AMovableBlock>(OtherActor);
	AFreezableBlock* FreezableBlock = Cast<AFreezableBlock>(OtherActor);
	if (Slime)
	{
		Slime->Damage(Damage);
	}
	// Check if the projectile hit a breakable block
	else if (BreakableBlock)
	{
		BreakableBlock->Damage(Damage);
	}
	// Check if the projectile hit a movable block
	else if (MovableBlock)
	{
		MovableBlock->Hit();
	}
	// Check if the projectile hit a freezable block
	else if(FreezableBlock)
	{
		FreezableBlock->Hit();
	}
	else if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
	// Destroy the projectile after the hit
	Destroy();
}
 
