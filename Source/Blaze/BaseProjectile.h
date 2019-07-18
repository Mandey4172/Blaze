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

	UFUNCTION(BlueprintCallable)
		class UMeshComponent* GetMeshComponent();

	UFUNCTION(BlueprintCallable)
		class UShapeComponent* GetColisionComponent();

	UFUNCTION(BlueprintCallable)
		class UMovementComponent* GetMovementComponent();

	UFUNCTION(BlueprintCallable)
		void SetInitialSpeed(const float& newInitialSpeed);
	UFUNCTION(BlueprintCallable)
		float GetInitialSpeed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
protected:
	UPROPERTY(VisibleAnywhere)
		class UMeshComponent* meshComponent;
	UPROPERTY(VisibleAnywhere)
		class UShapeComponent* colisionComponent;
	UPROPERTY(VisibleAnywhere)
		class UMovementComponent* movementComponent;
	UPROPERTY(EditAnywhere)
		float initialSpeed;
};
