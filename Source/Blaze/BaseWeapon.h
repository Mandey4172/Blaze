// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseProjectile.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class BLAZE_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* meshComponent;
	//protected:
	UPROPERTY(EditDefaultsOnly, Category = Damage)
		TSubclassOf<ABaseProjectile> projectileClass;
};
