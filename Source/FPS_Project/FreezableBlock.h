// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInterface.h"
#include "FreezableBlock.generated.h"

UENUM(BlueprintType)
enum class EFreezableBlockState : uint8
{
	MovingToEnd,
	FrozenMovingToEnd,
	FrozenMovingToStart,
	MovingToStart
};

UCLASS()
class FPS_PROJECT_API AFreezableBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFreezableBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Overridden reset function
	virtual void Reset() override;

	// Offset to move the block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	FVector Offset;

	// Movable block speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Speed = 1;

	// How many frames to keep the block frozen
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	int FrozenFrames;

	// Movable block state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	EFreezableBlockState BlockState;

	// Called when the block is hit by a projectile
	UFUNCTION()
	void Hit();

private:
	// Dynamic material of the block used to change its texture
	UMaterialInstanceDynamic* DynamicMaterial;

	// Block starting position
	FVector StartPosition;

	// Current block position
	FVector CurrentPosition;

	// Ending block position
	FVector EndPosition;

	// X increment per frame
	float XIncrement;

	// Y increment per frame
	float YIncrement;

	// Z increment per frame
	float ZIncrement;

	// Overlapped actors
	TSet<AActor*> OverlappingActors;

	// How long the block has been frozen
	int FrozenCounter = 0;
};
