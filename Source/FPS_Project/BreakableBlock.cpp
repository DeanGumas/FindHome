// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableBlock.h"

// Sets default values
ABreakableBlock::ABreakableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABreakableBlock::BeginPlay()
{
	Super::BeginPlay();

	// Create dynamic material for texture changing
	auto Mesh = FindComponentByClass<UStaticMeshComponent>();
	auto Material = Mesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	Mesh->SetMaterial(0, DynamicMaterial);
}

// Called every frame
void ABreakableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when the block is hit by something damaging
void ABreakableBlock::Damage(uint8 Amount)
{
	Health -= Amount;
	// Crack the block at 50% health
	if (Health == 50)
	{
		DynamicMaterial->SetScalarParameterValue(TEXT("IsCracked"), 1.0f);
	}
	// Destroy the block at 0% health
	else if (Health == 0)
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}

// Overridden reset function
void ABreakableBlock::Reset()
{
	Health = 100;
	DynamicMaterial->SetScalarParameterValue(TEXT("IsCracked"), 0.0f);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

