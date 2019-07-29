// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Engine.h"
#include "BaseWeapon.h"

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

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	InputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);

	InputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &APlayerCharacter::Attack);
}

void APlayerCharacter::EquipWeapon(TSubclassOf<class ABaseWeapon> newActiveWeaponClass)
{
	equpedWeaponClass = newActiveWeaponClass;
	UWorld * world = GetWorld();
	if (world && equpedWeaponClass)
	{
		equpedWeapon = world->SpawnActor<ABaseWeapon>(equpedWeaponClass);
		equpedWeapon->AttachToComponent(firstPersonMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, weaponMeshSocket);
	}
}

void APlayerCharacter::Attack()
{
	FVector location;
	FRotator rotation;
	GetActorEyesViewPoint(location, rotation);

	if (equpedWeapon)
		equpedWeapon->UseThis(GetActorLocation(), GetActorRotation());
}