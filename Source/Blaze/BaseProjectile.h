// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class BLAZE_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnFire(FVector direction);

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* meshComponent;
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* colisionComponent;
	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* movementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		float initialSpeed;
};
