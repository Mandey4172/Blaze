// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Engine.h"

// Sets default values
AItem::AItem() 

{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	//collisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Shape Component"));

	UBoxComponent * initialCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Item Collision Component"));
	initialCollisionComponent->SetupAttachment(GetRootComponent());
	collisionComponent = initialCollisionComponent;
	SetRootComponent(collisionComponent);

	UStaticMeshComponent* initialMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh Component"));
	initialMeshComponent->SetupAttachment(collisionComponent);
	meshComponent = initialMeshComponent;

	//InitBody(meshComponent, collisionComponent);
}

//AItem::AItem(class UMeshComponent* newMeshComponent, class UShapeComponent* newCollisionComponent)
//{
//	Init(newMeshComponent, newCollisionComponent);
//}

void AItem::InitBody(class UMeshComponent* uninitializedMeshComponent, class UShapeComponent* uninitializedCollisionComponent)
{
	uninitializedCollisionComponent->SetupAttachment(GetRootComponent());
	SetRootComponent(uninitializedCollisionComponent);

	uninitializedMeshComponent->SetupAttachment(uninitializedCollisionComponent);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

UMeshComponent * AItem::GetMeshComponent() const
{
	return meshComponent;
}

UShapeComponent * AItem::GetColisionComponent() const
{
	return collisionComponent;
}

void AItem::Use(ACharacter * owner)
{
}

void AItem::PickUp(ACharacter * itemOwner)
{
	if (meshComponent)
		meshComponent->SetVisibility(false);
	SetActorEnableCollision(false);
}

void AItem::Drop(ACharacter * itemOwner)
{
	if (meshComponent)
		meshComponent->SetVisibility(true);
	SetActorEnableCollision(true);
}

bool AItem::CanUse() const
{
	return true;
}

bool AItem::ShouldContinue() const
{
	return shouldContiniueUsing;
}

float AItem::GetCooldown() const
{
	return useCooldown;
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}