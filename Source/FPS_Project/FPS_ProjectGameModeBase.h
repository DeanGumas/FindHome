// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Slime.h"
#include "MovingBlock.h"
#include "MovableBlock.h"
#include "FreezableBlock.h"
#include "BreakableBlock.h"
#include "FPS_ProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FPS_PROJECT_API AFPS_ProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;

	virtual void ResetLevel() override;

	TArray<AActor*> Slimes;

	TArray<AActor*> MovingBlocks;

	TArray<AActor*> MovableBlocks;

	TArray<AActor*> FreezableBlocks;

	TArray<AActor*> BreakableBlocks;
};
