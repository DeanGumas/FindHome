// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingBlock.h"

// Sets default values
AMovingBlock::AMovingBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingBlock::BeginPlay()
{
	Super::BeginPlay();

	// Get start position
	StartPosition = GetActorLocation();

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
void AMovingBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update position based on movement direction
	if (MovingForward)
	{
		CurrentPosition.X += XIncrement;
		CurrentPosition.Y += YIncrement;
		CurrentPosition.Z += ZIncrement;
		if (CurrentPosition == EndPosition)
		{
			MovingForward = false;
		}
	}
	else
	{
		CurrentPosition.X -= XIncrement;
		CurrentPosition.Y -= YIncrement;
		CurrentPosition.Z -= ZIncrement;
		if (CurrentPosition == StartPosition)
		{
			MovingForward = true;
		}
	}
	SetActorLocation(CurrentPosition);

	// Check if overlapping other actors, if so reverse direction
	GetOverlappingActors(OverlappingActors, nullptr);
	if (OverlappingActors.Num() >= 1)
	{
		if (MovingForward)
		{
			MovingForward = false;
		}
		else
		{
			MovingForward = true;
		}
	}
}

