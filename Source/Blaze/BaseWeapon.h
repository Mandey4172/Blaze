// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseProjectile.h"
#include "Item.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class BLAZE_API ABaseWeapon : public AItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Use(class ACharacter * owner) override;

	UFUNCTION(BlueprintCallable)
		virtual void Shoot(FVector location, FRotator rotation);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
protected:
	UPROPERTY(EditAnywhere)
		FVector offset;
	UPROPERTY(EditDefaultsOnly, Category = Damage)
		TSubclassOf<class ABaseProjectile> projectileClass;
};
