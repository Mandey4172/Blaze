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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		virtual void UseThis(FVector location, FRotator rotation);
	UFUNCTION(BlueprintCallable)
		class UMeshComponent* GetMeshComponent();
	UFUNCTION(BlueprintCallable)
		class UShapeComponent* GetColisionComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
protected:
	UPROPERTY(EditAnywhere)
		FVector offset;
	UPROPERTY(VisibleAnywhere)
		class UMeshComponent* meshComponent;
	UPROPERTY(VisibleAnywhere)
		class UShapeComponent* collisionComponent;
	UPROPERTY(EditDefaultsOnly, Category = Damage)
		TSubclassOf<class ABaseProjectile> projectileClass;
};
