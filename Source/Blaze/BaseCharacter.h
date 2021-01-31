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
	/* Sets default values for this character's properties */
	ABaseCharacter();

	/* Called every frame */
	void Tick(float DeltaTime) override;

	/* Called to bind functionality to input */
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void MoveForward(float Value);
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		virtual void StartAttack();
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		virtual void StopAttack();
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		virtual void OnAttack();

	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		virtual void EquipWeapon(TSubclassOf<class ABaseWeapon> newActiveWeaponClass);

	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		virtual void PickupItem(class AItem* item);
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		virtual void DropItem(class AItem* item);

	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		class ABaseWeapon * GetEquipedWeapon() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		virtual FVector GetCharacterEyesLocation() const;
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		virtual FRotator GetCharacterEyesRotation() const;

public:
protected:
	UPROPERTY(EditDefaultsOnly, Category = "BaseCharacter")
		TSubclassOf<class ABaseWeapon> equpedWeaponClass;
	class ABaseWeapon * equippedWeapon;

	UPROPERTY(EditAnywhere, Category = "BaseCharacter")
		TArray<class AItem *> backpack;

	UPROPERTY(EditAnywhere)
		FVector rightHandOffset;
	/* Handle to manage the timer */
	FTimerHandle attactColdownHandle;
};
