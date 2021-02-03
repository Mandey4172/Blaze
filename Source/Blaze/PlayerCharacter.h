// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 *
 */
UCLASS()
class BLAZE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EquipWeapon(TSubclassOf<class ABaseWeapon> newActiveWeaponClass)override;
	void OnAttack() override;

	UFUNCTION(BlueprintCallable)
		class UCameraComponent* GetCameraComponent() const;
	UFUNCTION(BlueprintCallable)
		class USpringArmComponent* GetCameraSpringArmComponent() const;
	UFUNCTION(BlueprintCallable)
		class USkeletalMeshComponent* GetFirstPersonMeshComponent() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector GetCharacterEyesLocation() const override;

	FRotator GetCharacterEyesRotation() const override;

	//
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent * cameraComponent;
	//
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent * firstPersonMesh;
	//
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent * cameraSpringArm;

	float actionRange;

private:
	bool actionAvailable;
	AActor * actionActor;

	UFUNCTION(BlueprintCallable)
		void OnAction();
	UFUNCTION(BlueprintCallable)
		void SearchForAction();
};
