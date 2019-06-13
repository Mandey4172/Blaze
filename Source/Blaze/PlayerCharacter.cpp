// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Engine.h"

APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	cameraSpringArm->SetupAttachment(GetRootComponent());
	cameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(0.0f, 0.0f, 0.0f));
	cameraSpringArm->TargetArmLength = 10.f;
	cameraSpringArm->bEnableCameraLag = true;
	cameraSpringArm->CameraLagSpeed = 3.0f;

	cameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	cameraComponent->SetupAttachment(cameraSpringArm, USpringArmComponent::SocketName);

	firstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>("First Person Mesh");
	firstPersonMesh->AttachTo(GetRootComponent());
	firstPersonMesh->SetOnlyOwnerSee(true);

	GetMesh()->SetOwnerNoSee(true);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

	InputComponent->BindAxis("Turn", this, &ABaseCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &ABaseCharacter::AddControllerPitchInput);
}