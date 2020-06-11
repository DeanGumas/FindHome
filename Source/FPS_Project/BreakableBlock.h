// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInterface.h"
#include "BreakableBlock.generated.h"

UCLASS()
class FPS_PROJECT_API ABreakableBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to damage the block
	UFUNCTION()
	void Damage(uint8 Amount);

private:
	// Dynamic material of the block used to change its texture
	UMaterialInstanceDynamic* DynamicMaterial;

	// Number of shots it takes to break the block
	uint8 Health = 100;
};
