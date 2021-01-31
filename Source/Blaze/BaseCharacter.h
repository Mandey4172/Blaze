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
	virtual void Tick(float DeltaTime) override;

	/* Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "BCharacter")
		void MoveForward(float Value);
	UFUNCTION(BlueprintCallable, Category = "BCharacter")
		void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category = "BCharacter")
		virtual void StartAttack();
	UFUNCTION(BlueprintCallable, Category = "BCharacter")
		virtual void StopAttack();
	UFUNCTION(BlueprintCallable, Category = "BCharacter")
		virtual void OnAttack();

	UFUNCTION(BlueprintCallable, Category = "BCharacter")
		virtual void EquipWeapon(TSubclassOf<class ABaseWeapon> newActiveWeaponClass);

	UFUNCTION(BlueprintCallable, Category = "BCharacter")
		virtual void PickupItem(class AItem* item);
	UFUNCTION(BlueprintCallable, Category = "BCharacter")
		virtual void DropItem(class AItem* item);

	UFUNCTION(BlueprintCallable, Category = "BCharacter")
		class ABaseWeapon * GetEquipedWeapon() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
protected:
	UPROPERTY(EditDefaultsOnly, Category = "BCharacter")
		TSubclassOf<class ABaseWeapon> equpedWeaponClass;
	class ABaseWeapon * equippedWeapon;

	UPROPERTY(EditAnywhere, Category = "BCharacter")
		TArray<class AItem *> backpack;

	UPROPERTY(EditAnywhere)
		FVector rightHandOffset;
	/* Handle to manage the timer */
	FTimerHandle attactColdownHandle;
};
