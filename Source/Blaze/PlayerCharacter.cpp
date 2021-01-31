// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Engine.h"
#include "BaseWeapon.h"
#include "DrawDebugHelpers.h"

APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	cameraSpringArm->SetupAttachment(GetRootComponent());
	cameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(0.0f, 0.0f, 0.0f));
	cameraSpringArm->TargetArmLength = 10.f;
	cameraSpringArm->bEnableCameraLag = false;
	cameraSpringArm->CameraLagMaxDistance = 10.f;

	cameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	cameraComponent->SetupAttachment(cameraSpringArm, USpringArmComponent::SocketName);
	cameraComponent->bUsePawnControlRotation = true;

	firstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>("First Person Mesh");
	firstPersonMesh->AttachTo(GetRootComponent());
	firstPersonMesh->SetOnlyOwnerSee(true);

	GetMesh()->SetOwnerNoSee(true);

	actionRange = 1000.f;

	actionAvailable = false;
	actionActor = nullptr;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SearchForAction();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	InputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);

	InputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &APlayerCharacter::StartAttack);
	InputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &APlayerCharacter::StopAttack);

	InputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &APlayerCharacter::OnAction);
}

void APlayerCharacter::SearchForAction()
{
	UWorld* world = GetWorld();
	if (world)
	{
		FHitResult hitResoult;
		FVector playerLocation;
		FRotator playerRotation;
		GetActorEyesViewPoint(playerLocation, playerRotation);
		const FVector offset = actionRange * FVector(1.f, 0.f, 0.f);
		const FVector endLocation = playerLocation + FTransform(playerRotation).TransformVector(offset);

		DrawDebugLine(world, playerLocation, endLocation, FColor::Red, false, -1.f, 0, 1.f);

		if (world->LineTraceSingleByChannel(hitResoult, playerLocation, endLocation, ECollisionChannel::ECC_Visibility))
		{
			actionAvailable = true;
			actionActor = hitResoult.GetActor();
		}
		else
		{
			actionAvailable = false;
			actionActor = nullptr;
		}
	}
}

void APlayerCharacter::OnAction()
{
	if (actionAvailable)
	{
		if (actionActor)
		{
			AItem * item = Cast<AItem>(actionActor);
			if (item)
			{
				PickupItem(item);
			}
		}
	}
}

void APlayerCharacter::OnAttack()
{
	if (equippedWeapon)
		equippedWeapon->Use(this);
}

UCameraComponent * APlayerCharacter::GetCameraComponent() const
{
	return cameraComponent;
}

USpringArmComponent * APlayerCharacter::GetCameraSpringArmComponent() const
{
	return cameraSpringArm;
}

USkeletalMeshComponent * APlayerCharacter::GetFirstPersonMeshComponent() const
{
	return firstPersonMesh;
}