// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
#include "Engine.h"
#include "BaseProjectile.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	collisionComponent->SetupAttachment(GetRootComponent());

	meshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	meshComponent->SetupAttachment(collisionComponent);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::Shoot()
{
	UWorld* world = GetWorld();
	if (world)
	{
		FVector location = GetActorLocation() + offset;
		FRotator rotation = GetActorRotation();
		ABaseProjectile * projectile = world->SpawnActor<ABaseProjectile>(projectileClass, location, rotation);
		if (projectile)
			projectile->OnFire(rotation.Vector());
	}
}