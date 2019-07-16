// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"
#include "Engine.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	colisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collicion Component"));
	colisionComponent->SetupAttachment(GetRootComponent());

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComponent->SetupAttachment(colisionComponent);

	movementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	movementComponent->Velocity = FVector::ZeroVector;
	movementComponent->ProjectileGravityScale = 0;
	initialSpeed = 10000.f;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseProjectile::OnFire(FVector direction)
{
	movementComponent->Velocity = initialSpeed * direction.GetClampedToMaxSize(1.0f);
}