// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Engine.h"
#include "BaseWeapon.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCharacterMovementComponent * movementComponent = GetCharacterMovement();
	if (movementComponent)
	{
		movementComponent->MaxAcceleration = 2800.f;
		movementComponent->BrakingFriction = 5;
		movementComponent->bUseSeparateBrakingFriction = true;

		movementComponent->SetWalkableFloorAngle(45.f);
		movementComponent->GroundFriction = 10.5f;
		movementComponent->MaxWalkSpeed = 520.f;
		movementComponent->MaxWalkSpeedCrouched = 250.f;
		movementComponent->BrakingDecelerationWalking = 620.f;

		movementComponent->JumpZVelocity = 520.f;
		movementComponent->AirControl = 0.55f;
		movementComponent->AirControlBoostVelocityThreshold = 5.f;

		movementComponent->NavWalkingFloorDistTolerance = 5.f;
	}
	equpedWeaponClass = ABaseWeapon::StaticClass();
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	EquipWeapon(equpedWeaponClass);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::X).GetClampedToMaxSize(1.f);
	AddMovementInput(Direction, Value);
}

void ABaseCharacter::EquipWeapon(TSubclassOf<class ABaseWeapon> newActiveWeaponClass)
{
	equpedWeaponClass = newActiveWeaponClass;
	UWorld * world = GetWorld();
	if (world && equpedWeaponClass)
	{
		equpedWeapon = world->SpawnActor<ABaseWeapon>(equpedWeaponClass);
		equpedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, weaponMeshSocket);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::Y).GetClampedToMaxSize(1.f);
	AddMovementInput(Direction, Value);
}

void ABaseCharacter::StartAttack()
{
	if (equpedWeapon)
	{
		if (equpedWeapon->CanShoot())
		{
			OnAttack();
			if (equpedWeapon->ShouldContinue())
			{
				UWorld * world = GetWorld();
				if (world)
					world->GetTimerManager().SetTimer(attactColdownHandle, this, &ABaseCharacter::StartAttack, equpedWeapon->GetCooldown(), false);
			}
		}
	}
}

void ABaseCharacter::StopAttack()
{
	GetWorld()->GetTimerManager().ClearTimer(attactColdownHandle);
}

void ABaseCharacter::OnAttack()
{
	if (equpedWeapon)
		equpedWeapon->Shoot(GetActorLocation(), GetActorRotation());
}

ABaseWeapon* ABaseCharacter::GetEquipedWeapon()
{
	return equpedWeapon;
}