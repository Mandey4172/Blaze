// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Engine.h"

AItem::AItem() : AItem(true)
{

}

AItem::AItem(bool createComponents)
{
	PrimaryActorTick.bCanEverTick = false;
	if (createComponents)
	{
		UBoxComponent* initialCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Item Collision Component"));
		initialCollisionComponent->SetupAttachment(GetRootComponent());
		collisionComponent = initialCollisionComponent;
		SetRootComponent(collisionComponent);

		UStaticMeshComponent* initialMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh Component"));
		initialMeshComponent->SetupAttachment(collisionComponent);
		meshComponent = initialMeshComponent;
	}
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