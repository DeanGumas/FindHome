// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInterface.h"
#include "MovableBlock.generated.h"

UENUM(BlueprintType)
enum class EMovableBlockState : uint8
{
	Start,
	MovingToEnd,
	End, 
	MovingToStart
};

UCLASS()
class FPS_PROJECT_API AMovableBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovableBlock();

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

	// Movable block state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	EMovableBlockState BlockState;

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
};
