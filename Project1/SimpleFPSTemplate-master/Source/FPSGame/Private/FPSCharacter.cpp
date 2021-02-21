// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimSequence.h"


AFPSCharacter::AFPSCharacter()
{
	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(0, 0, BaseEyeHeight)); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1PComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	Mesh1PComponent->SetupAttachment(CameraComponent);
	Mesh1PComponent->CastShadow = false;
	Mesh1PComponent->SetRelativeRotation(FRotator(2.0f, -15.0f, 5.0f));
	Mesh1PComponent->SetRelativeLocation(FVector(0, 0, -160.0f));

	// Create a gun mesh component
	GunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	GunMeshComponent->CastShadow = false;
	GunMeshComponent->SetupAttachment(Mesh1PComponent, "GripPoint");
}


void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
	PlayerInputComponent->BindAction("FireBombDown", IE_Pressed, this, &AFPSCharacter::FireBombDown);
	PlayerInputComponent->BindAction("FireBomb", IE_Released, this, &AFPSCharacter::FireBomb);
	

	PlayerInputComponent->BindAction("SpawnBomb", IE_Pressed, this, &AFPSCharacter::SpawnBomb);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}


void AFPSCharacter::Fire()
{
	// try and fire a projectile
	if (ProjectileClass)
	{
		// Grabs location from the mesh that must have a socket called "Muzzle" in his skeleton
		FVector MuzzleLocation = GunMeshComponent->GetSocketLocation("Muzzle");
		// Use controller rotation which is our view direction in first person
		FRotator MuzzleRotation = GetControlRotation();

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the projectile at the muzzle
		GetWorld()->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, ActorSpawnParams);
	}

	// try and play the sound if specified
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1PComponent->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->PlaySlotAnimationAsDynamicMontage(FireAnimation, "Arms", 0.0f);
		}
	}
}

void AFPSCharacter::FireBomb()
{
	float timeDown2 = GetWorld()->TimeSeconds;
	timeDown2 -= timeDown;

	//this was given to me by Ben but I couldn't get it to function properly so I attempted to determine how long the button was held by getting the world time when the button is pressed and again when released
	// Link -> https://answers.unrealengine.com/questions/569883/getting-input-key-time-down-in-c.html
	timeDown = GetWorld()->GetFirstPlayerController()->GetInputKeyTimeDown(FKey("LeftShift"));

	/*if(timeDown <= 0.0f)
	{
		GetWorld()->GetFirstPlayerController()->GetInputKeyTimeDown(FKey("RightShift"));
	}*/

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("timeDown = " + FString::SanitizeFloat(timeDown) + "\ntimeDown2 = " + FString::SanitizeFloat(timeDown2)));

	if(timeDown2 <= 1.0f && !bCooldown)
	{
		Fire();
		bCooldown = true;
	}
	else if(timeDown2 <= 2.5f && timeDown > 1.0f && !bCooldown)
	{
		Fire();
		Fire();
		Fire();
		bCooldown = true;
	}
	else if(timeDown2 > 2.5f && !bCooldown)
	{
		Fire();
		Fire();
		Fire();
		Fire();
		Fire();
		bCooldown = true;
	}
	else
	{
		//do nothing because it's on cooldown
	}

	FTimerHandle weaponCooldown;

	if(bCooldown)
	{
		//GetWorldTimerManager().SetTimer<AFPSCharacter>(weaponCooldown, this, AFPSCharacter::FireBombCooldown(), 3.0f, false);
		GetWorldTimerManager().SetTimer(weaponCooldown, this, &AFPSCharacter::FireBombCooldown, 3.0f);
	}
}

void AFPSCharacter::FireBombDown()
{
	//timeDown = GetWorld()->DeltaTimeSeconds;
	timeDown = GetWorld()->TimeSeconds;
}

void AFPSCharacter::FireBombCooldown()
{
	bCooldown = false;
}

void AFPSCharacter::SpawnBomb() 
{

	AActor* MyMomb = GetWorld()->SpawnActor<AActor>(BombClass, GetActorLocation(), GetActorRotation());
}


void AFPSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}


void AFPSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}
