// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableBlock.h"

// Sets default values
AMovableBlock::AMovableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovableBlock::BeginPlay()
{
	Super::BeginPlay();
	
	// Create dynamic material for texture changing
	auto Mesh = FindComponentByClass<UStaticMeshComponent>();
	auto Material = Mesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	Mesh->SetMaterial(0, DynamicMaterial);

	// Get start position and set state to start
	StartPosition = GetActorLocation();
	BlockState = EMovableBlockState::Start;

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
void AMovableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (BlockState)
	{
	case EMovableBlockState::MovingToEnd:
		CurrentPosition.X += XIncrement;
		CurrentPosition.Y += YIncrement;
		CurrentPosition.Z += ZIncrement;
		if (CurrentPosition == EndPosition)
		{
			BlockState = EMovableBlockState::End;
			DynamicMaterial->SetScalarParameterValue(TEXT("IsMoving"), 0.0f);
		}
		SetActorLocation(CurrentPosition);
		break;
	case EMovableBlockState::MovingToStart:
		CurrentPosition.X -= XIncrement;
		CurrentPosition.Y -= YIncrement;
		CurrentPosition.Z -= ZIncrement;
		if (CurrentPosition == StartPosition)
		{
			BlockState = EMovableBlockState::Start;
			DynamicMaterial->SetScalarParameterValue(TEXT("IsMoving"), 0.0f);
		}
		SetActorLocation(CurrentPosition);
		break;
	}
	GetOverlappingActors(OverlappingActors, nullptr);
	if (OverlappingActors.Num() >= 1)
	{
		switch (BlockState)
		{
		case EMovableBlockState::MovingToEnd:
			BlockState = EMovableBlockState::MovingToStart;
			break;
		case EMovableBlockState::MovingToStart:
			BlockState = EMovableBlockState::MovingToEnd;
			break;
		}
	}
}

// Called when the block is hit by a projectile
void AMovableBlock::Hit()
{
	// If the block is not currently moving, start moving towards the start or end position
	// If it is already moving, start moving in the opposite direction
	// Also change texture
	switch (BlockState)
	{
	case EMovableBlockState::Start:
		BlockState = EMovableBlockState::MovingToEnd;
		DynamicMaterial->SetScalarParameterValue(TEXT("IsMoving"), 1.0f);
		break;
	case EMovableBlockState::MovingToEnd:
		BlockState = EMovableBlockState::MovingToStart;
		break;
	case EMovableBlockState::MovingToStart:
		BlockState = EMovableBlockState::MovingToEnd;
		break;
	case EMovableBlockState::End:
		BlockState = EMovableBlockState::MovingToStart;
		DynamicMaterial->SetScalarParameterValue(TEXT("IsMoving"), 1.0f);
		break;
	}
}
