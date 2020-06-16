// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPS_ProjectGameModeBase.h"
#include "FPS_Project.h"

void AFPS_ProjectGameModeBase::StartPlay()
{
	Super::StartPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASlime::StaticClass(), Slimes);
}

void AFPS_ProjectGameModeBase::ResetLevel()
{
	StartPlay();
	for (int i = 0; i < Slimes.Num(); i++)
	{
		if (Slimes[i])
		{
			Slimes[i]->Reset();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hi")));
		}
	}
}
