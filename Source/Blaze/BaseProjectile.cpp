// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"
#include "Engine.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent * initialColisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collicion Component"));
	initialColisionComponent->SetupAttachment(GetRootComponent());
	collisionComponent = initialColisionComponent;
	SetRootComponent(collisionComponent);

	UStaticMeshComponent * initialMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	initialMeshComponent->SetupAttachment(collisionComponent);
	meshComponent = initialMeshComponent;

	UProjectileMovementComponent * initialMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	initialMovementComponent->Velocity = FVector::ZeroVector;
	initialMovementComponent->ProjectileGravityScale = 0;
	movementComponent = initialMovementComponent;

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

UMeshComponent * ABaseProjectile::GetMeshComponent()
{
	return meshComponent;
}

UShapeComponent* ABaseProjectile::GetColisionComponent()
{
	return collisionComponent;
}

UMovementComponent* ABaseProjectile::GetMovementComponent()
{
	return movementComponent;
}

float ABaseProjectile::GetInitialSpeed()
{
	return initialSpeed;
}

void ABaseProjectile::SetInitialSpeed(const float& newInitialSpeed)
{
	initialSpeed = newInitialSpeed;
}