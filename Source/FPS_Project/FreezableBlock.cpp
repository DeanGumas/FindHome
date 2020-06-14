// Fill out your copyright notice in the Description page of Project Settings.


#include "FreezableBlock.h"

// Sets default values
AFreezableBlock::AFreezableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFreezableBlock::BeginPlay()
{
	Super::BeginPlay();
	
	// Create dynamic material for texture changing
	auto Mesh = FindComponentByClass<UStaticMeshComponent>();
	auto Material = Mesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	Mesh->SetMaterial(0, DynamicMaterial);

	// Get start position and set state to start
	StartPosition = GetActorLocation();
	BlockState = EFreezableBlockState::MovingToEnd;

	// Determine increment values in each cardinal direction
	if (Offset.X < 0)
	{
		XIncrement = -Speed;
	}
	else if (Offset.X > 0)
	{
		XIncrement = Speed;
	}
	else
	{
		XIncrement = 0;
	}
	// Y Direction
	if (Offset.Y < 0)
	{
		YIncrement = -Speed;
	}
	else if (Offset.Y > 0)
	{
		YIncrement = Speed;
	}
	else
	{
		YIncrement = 0;
	}
	// Z Direction
	if (Offset.Z < 0)
	{
		ZIncrement = -Speed;
	}
	else if (Offset.Z > 0)
	{
		ZIncrement = Speed;
	}
	else
	{
		ZIncrement = 0;
	}

	// Set End position based off the offset
	EndPosition.X = StartPosition.X + Offset.X;
	EndPosition.Y = StartPosition.Y + Offset.Y;
	EndPosition.Z = StartPosition.Z + Offset.Z;

	// Set current position
	CurrentPosition = StartPosition;
}

// Called every frame
void AFreezableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (BlockState)
	{
	case EFreezableBlockState::MovingToEnd:
		CurrentPosition.X += XIncrement;
		CurrentPosition.Y += YIncrement;
		CurrentPosition.Z += ZIncrement;
		if (CurrentPosition == EndPosition)
		{
			BlockState = EFreezableBlockState::MovingToStart;
		}
		SetActorLocation(CurrentPosition);
		break;
	case EFreezableBlockState::FrozenMovingToEnd:
		FrozenCounter++;
		if (FrozenCounter == FrozenFrames)
		{
			FrozenCounter = 0;
			DynamicMaterial->SetScalarParameterValue(TEXT("IsFrozen"), 0.0f);
			BlockState = EFreezableBlockState::MovingToEnd;
		}
		break;
	case EFreezableBlockState::FrozenMovingToStart:
		FrozenCounter++;
		if (FrozenCounter == FrozenFrames)
		{
			FrozenCounter = 0;
			DynamicMaterial->SetScalarParameterValue(TEXT("IsFrozen"), 0.0f);
			BlockState = EFreezableBlockState::MovingToStart;
		}
		break;
	case EFreezableBlockState::MovingToStart:
		CurrentPosition.X -= XIncrement;
		CurrentPosition.Y -= YIncrement;
		CurrentPosition.Z -= ZIncrement;
		if (CurrentPosition == StartPosition)
		{
			BlockState = EFreezableBlockState::MovingToEnd;
		}
		SetActorLocation(CurrentPosition);
		break;
	}

}

// Called when the block is hit by a projectile
void AFreezableBlock::Hit()
{
	switch (BlockState)
	{
	case EFreezableBlockState::MovingToEnd:
		BlockState = EFreezableBlockState::FrozenMovingToEnd;
		DynamicMaterial->SetScalarParameterValue(TEXT("IsFrozen"), 1.0f);
		break;
	case EFreezableBlockState::MovingToStart:
		BlockState = EFreezableBlockState::FrozenMovingToStart;
		DynamicMaterial->SetScalarParameterValue(TEXT("IsFrozen"), 1.0f);
		break;
	}
}

