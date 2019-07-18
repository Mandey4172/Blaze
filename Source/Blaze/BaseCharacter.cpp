// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Engine.h"
#include "BaseWeapon.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void ABaseCharacter::EquipWeapon(TSubclassOf<class ABaseWeapon> newActiveWeaponClass)
{
	equpedWeaponClass = newActiveWeaponClass;
	UWorld * world = GetWorld();
	if (world && equpedWeaponClass)
	{
		equpedWeapon = world->SpawnActor<ABaseWeapon>(equpedWeaponClass);
	}
}

ABaseWeapon* ABaseCharacter::GetEquipedWeapon()
{
	return equpedWeapon;
}