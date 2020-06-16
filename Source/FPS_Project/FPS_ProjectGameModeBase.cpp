// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPS_ProjectGameModeBase.h"
#include "FPS_Project.h"

void AFPS_ProjectGameModeBase::StartPlay()
{
	Super::StartPlay();

	// Get all instances of actors that need to be reset upon character respawn
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASlime::StaticClass(), Slimes);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMovingBlock::StaticClass(), MovingBlocks);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMovableBlock::StaticClass(), MovableBlocks);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFreezableBlock::StaticClass(), FreezableBlocks);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABreakableBlock::StaticClass(), BreakableBlocks);
}

void AFPS_ProjectGameModeBase::ResetLevel()
{
	// Loop through all slimes and reset them
	for (int i = 0; i < Slimes.Num(); i++)
	{
		if (Slimes[i])
		{
			Slimes[i]->Reset();
		}
	}

	// Loop through all moving blocks and reset them
	for (int i = 0; i < MovingBlocks.Num(); i++)
	{
		if (MovingBlocks[i])
		{
			MovingBlocks[i]->Reset();
		}
	}

	// Loop through all movable blocks and reset them
	for (int i = 0; i < MovableBlocks.Num(); i++)
	{
		if (MovableBlocks[i])
		{
			MovableBlocks[i]->Reset();
		}
	}

	// Loop through all freezable blocks and reset them
	for (int i = 0; i < FreezableBlocks.Num(); i++)
	{
		if (FreezableBlocks[i])
		{
			FreezableBlocks[i]->Reset();
		}
	}

	// Loop through all breakable blocks and reset them
	for (int i = 0; i < BreakableBlocks.Num(); i++)
	{
		if (BreakableBlocks[i])
		{
			BreakableBlocks[i]->Reset();
		}
	}
}
