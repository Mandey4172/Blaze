// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TItem.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class BLAZE_API AItem : public AActor //TAItem<UStaticMeshComponent, UBoxComponent>
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();
	AItem(bool createComponents);


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		virtual void Use(class ACharacter * itemOwner);
	UFUNCTION(BlueprintCallable)
		virtual void PickUp(class ACharacter * itemOwner);
	UFUNCTION(BlueprintCallable)
		virtual void Drop(class ACharacter * itemOwner);
	UFUNCTION(BlueprintCallable)
		virtual bool CanUse() const;
	UFUNCTION(BlueprintCallable)
		virtual bool ShouldContinue() const;
	UFUNCTION(BlueprintCallable)
		virtual float GetCooldown() const;
	UFUNCTION(BlueprintCallable)
		virtual class UMeshComponent * GetMeshComponent() const;
	UFUNCTION(BlueprintCallable)
		virtual class UShapeComponent* GetColisionComponent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
protected:
	UPROPERTY(EditAnywhere)
		bool shouldContiniueUsing;
	UPROPERTY(EditAnywhere)
		float useCooldown;
	UPROPERTY(VisibleAnywhere)
		class UMeshComponent * meshComponent;
	UPROPERTY(VisibleAnywhere)
		class UShapeComponent * collisionComponent;
};
