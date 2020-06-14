// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingBlock.generated.h"

UCLASS()
class FPS_PROJECT_API AMovingBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Offset to move the block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	FVector Offset;

	// Movable block speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Speed = 1;

private:
	// Boolean to determine which way the block is currently moving
	bool MovingForward = true;

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
};
