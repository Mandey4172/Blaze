// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class BLAZE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		void MoveForward(float Value);
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		void MoveRight(float Value);

	UFUNCTION(BlueprintCallable)
		virtual void Attack();

	UFUNCTION(BlueprintCallable)
		virtual void EquipWeapon(TSubclassOf<class ABaseWeapon> newActiveWeaponClass);
	UFUNCTION(BlueprintCallable)
		class ABaseWeapon* GetEquipedWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
protected:
	UPROPERTY(EditDefaultsOnly, Category = Damage)
		TSubclassOf<class ABaseWeapon> equpedWeaponClass;
	class ABaseWeapon * equpedWeapon;

	const FName weaponMeshSocket = TEXT("WeaponMeshSocket");
};
