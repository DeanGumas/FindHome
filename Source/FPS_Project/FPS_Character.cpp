// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_Character.h"

// Sets default values
AFPS_Character::AFPS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component
	FPS_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	// Attach the camera component to our capsule component
	FPS_CameraComponent->SetupAttachment(GetCapsuleComponent());

	// Position the camera above eye level
	FPS_CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// Allow the pawn to control camera rotation
	FPS_CameraComponent->bUsePawnControlRotation = true;

	// Create a first person mesh component for the owning player.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	// Only the owning player sees this mesh.
	FPSMesh->SetOnlyOwnerSee(true);
	// Attach the FPS mesh to the FPS camera.
	FPSMesh->SetupAttachment(FPS_CameraComponent);
	// Disable some environmental shadowing to preserve the illusion of having a single mesh.
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// The owning player doesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee(true);

	// Set character state to standing
	CharacterState = ECharState::Standing;
}

// Called when the game starts or when spawned
void AFPS_Character::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Velocity = GetVelocity();

	// Check if the character landed and is stationary in the X and Y directions
	if (Velocity.IsNearlyZero() && CharacterState != ECharState::JumpSquat && CharacterState != ECharState::RightShot && CharacterState != ECharState::LeftShot)
	{
		CharacterState = ECharState::Standing;
		Sprint = false;
		WalkSpeed = MinWalkSpeed;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}

	// Check if the character landed but is still moving in the X or Y directions
	if (!Velocity.IsNearlyZero() && CharacterState != ECharState::JumpSquat && CharacterState != ECharState::Jump)
	{
		CharacterState = ECharState::Running;
	}

	// Check if the character has peaked during their jump or if they have landed
	if (CharacterState == ECharState::Jump && fabs(Velocity.Z) <= 0.05)
	{
		if (Peaked)
		{
			CharacterState = ECharState::Standing;
			Peaked = false;
			ApplyFallDamage();
		}
		else
		{
			Peaked = true;
		}
	}

	// Check if the character fell off something and their Z velocity is negative
	if (CharacterState != ECharState::Jump && Velocity.Z < -500)
	{
		CharacterState = ECharState::Jump;
	}

	// Increment JumpSquat towards jump state
	if (CharacterState == ECharState::JumpSquat)
	{
		SquatFrames++;
		if (SquatFrames == JumpSquatFrames)
		{
			CharacterState = ECharState::Jump;
			bPressedJump = true;
			SquatFrames = 0;
		}
	}

	// Continue shooting projectiles while the player is shooting
	if (StillShooting)
	{
		ShootFrames++;
		if (ShootFrames == ShootFrequency)
		{
			Shoot();
			ShootFrames = 0;
		}
	}

	// Check if the character is falling fast enough to take fall damage
	if (Velocity.Z < (FallDamageVelocity * 3))
	{
		FallDamage = 3;
	}
	else if (Velocity.Z < (FallDamageVelocity * 2))
	{
		FallDamage = 2;
	}
	else if (Velocity.Z < FallDamageVelocity)
	{
		FallDamage = 1;
	}

	// Check if the character has fallen down too far, if so respawn them
	if (GetActorLocation().Z < -20000)
	{
		Respawn();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), Velocity.Z));
}

// Called to bind functionality to input
void AFPS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPS_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPS_Character::MoveRight);

	// Set up look bindings
	PlayerInputComponent->BindAxis("Turn", this, &AFPS_Character::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPS_Character::AddControllerPitchInput);

	// Set up action bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPS_Character::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPS_Character::StopJump);

	// Set up shooting bindings
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AFPS_Character::StartShooting);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AFPS_Character::StopShooting);

	// Set up sign reading bindings
	PlayerInputComponent->BindAction("Read", IE_Pressed, this, &AFPS_Character::StartStopReading);

	// Set up sprint bindings
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPS_Character::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFPS_Character::StopSprinting);
}

// Handle moving forward
void AFPS_Character::MoveForward(float Value)
{
	// Find out which way is forward and record that the player wants to move in that direction
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	// Use temporary 2D vector to normalize the direction vector along the X and Y axes
	FVector2D temp;
	temp.X = Direction.X;
	temp.Y = Direction.Y;
	temp.Normalize(0.0f);
	Direction.X = temp.X;
	Direction.Y = temp.Y;

	// If sprinting, update the maximum walk speed accordingly
	if (Sprint)
	{
		if (WalkSpeed < MaxWalkSpeed)
		{
			WalkSpeed += Acceleration;
		}
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}

	// Only allow movement if the character is not reading a sign
	if (!Reading)
	{
		AddMovementInput(Direction, Value);
	}
}

// Handle moving side to side
void AFPS_Character::MoveRight(float Value)
{
	// Find out which was is right and record the player wants to move in that direction, scale to half speed of running forward
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y)/2;
	
	// Only allow movement if the character is not reading a sign
	if (!Reading)
	{
		AddMovementInput(Direction, Value);
	}
}

// Handle jump start
void AFPS_Character::StartJump()
{
	CharacterState = ECharState::JumpSquat;
}

// Handle jump released
void AFPS_Character::StopJump()
{
	bPressedJump = false;
}

// Handle shooting basic projectile
void AFPS_Character::Shoot()
{
	// Attempt to fire a projectile
	if (ProjectileClass)
	{
		// Get the camera transform
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Decide if shooting with left or right gun and determine lateral offset accordingly
		if (RightShot)
		{
			MuzzleOffset.Y = DualWieldOffset;
			RightShot = false;
			if (CharacterState == ECharState::Standing || CharacterState == ECharState::LeftShot)
			{
				CharacterState = ECharState::RightShot;
			}
		}
		else
		{
			MuzzleOffset.Y = -DualWieldOffset;
			RightShot = true;
			if (CharacterState == ECharState::Standing || CharacterState == ECharState::RightShot)
			{
				CharacterState = ECharState::LeftShot;
			}
		}

		// Get Muzzle rotation
		FRotator MuzzleRotation = CameraRotation;

		// Get offset adjusted based on pitch
		FVector AdjustedOffset = MuzzleOffset;
		float Pitch = MuzzleRotation.Pitch;
		if (Pitch > 90)
		{
			Pitch = 360 - Pitch;
		}
		AdjustedOffset.Z -= (3 * Pitch / 4);

		// Transform MuzzleOffset from camera space to world space
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(AdjustedOffset);

		// Skew the aim slightly upwards
		//MuzzleRotation.Pitch += MuzzleAngle;

		UWorld* World = GetWorld();

		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;

			// Spawn the projectile at the muzzle
			ABasicProjectile* Projectile = World->SpawnActor<ABasicProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->ShootInDirection(LaunchDirection);
			}
		}
	}
}

// Function to start character shooting projectiles
void AFPS_Character::StartShooting()
{
	StillShooting = true;
	ShootFrames = 0;
	Shoot();
}

// Function to stop character shooting projectiles and update state if necessary
void AFPS_Character::StopShooting()
{
	if (CharacterState == ECharState::Shooting || CharacterState == ECharState::RightShot || CharacterState == ECharState::LeftShot)
	{
		CharacterState = ECharState::Standing;
	}
	StillShooting = false;
	ShootFrames = 0;
}

// Function to take damage by the specified amount
void AFPS_Character::Damage(uint8 Amount)
{
	Health -= Amount;
	if (Health == 0)
	{
		Respawn();
	}
}

// Function to collect a gem
void AFPS_Character::GetGem()
{
	Gems += 1;
}

// Function to respawn the character
void AFPS_Character::Respawn()
{
	Health = 3;
	if (RespawnLocation)
	{
		SetActorLocation(RespawnLocation->Location);
	}
	else
	{
		SetActorLocation(FVector(0, 0, 0));
	}
	GetWorld()->GetAuthGameMode()->ResetLevel();
}

// Function to set the players respawn location
void AFPS_Character::SetRespawnLocation(ARespawnFlag* Flag)
{
	if (RespawnLocation)
	{
		RespawnLocation->SetInactive();
	}
	RespawnLocation = Flag;
}

// Start or stop reading a sign if within range
void AFPS_Character::StartStopReading()
{
	if (CanRead)
	{
		CanRead = false;
	}
	else
	{
		CanRead = true;
	}
}

// Start sprinting
void AFPS_Character::StartSprinting()
{
	Sprint = true;
}

// Stop sprinting
void AFPS_Character::StopSprinting()
{
	Sprint = false;
}

// Function to apply fall damage
void AFPS_Character::ApplyFallDamage()
{
	Health -= FallDamage;
	FallDamage = 0;
	if (Health == 0)
	{
		Respawn();
	}
}