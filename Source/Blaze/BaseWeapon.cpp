// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
#include "Engine.h"
#include "BaseProjectile.h"
#include "BaseCharacter.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//UBoxComponent * initialCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Collision Component"));
	//initialCollisionComponent->SetupAttachment(GetRootComponent());
	//collisionComponent = initialCollisionComponent;
	//SetRootComponent(collisionComponent);

	//USkeletalMeshComponent * initialMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	//initialMeshComponent->SetupAttachment(collisionComponent);
	//meshComponent = initialMeshComponent;

	useCooldown = 0.5f;
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

void ABaseWeapon::Use(ACharacter * owner)
{
	if (owner)
	{ 
		FVector location;
		FRotator rotation;
		owner->GetActorEyesViewPoint(location, rotation);
		Shoot(location, rotation);
	}
}

void ABaseWeapon::Shoot(FVector location, FRotator rotation)
{
	UWorld* world = GetWorld();
	if (world)
	{
		location = location + FTransform(rotation).TransformVector(offset);
		ABaseProjectile * projectile = world->SpawnActor<ABaseProjectile>(projectileClass, location, rotation);
		if (projectile)
			projectile->OnFire(rotation.Vector());
	}
}