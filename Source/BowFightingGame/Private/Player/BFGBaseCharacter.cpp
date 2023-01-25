// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BFGBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BFGCharacterMovementComponent.h"
#include "Components/BFGWeaponComoponent.h"
#include "TimerManager.h"

float ChangesInLevelAim = 1;

ABFGBaseCharacter::ABFGBaseCharacter(const FObjectInitializer& Objinit) : Super(Objinit.SetDefaultSubobjectClass<UBFGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	WeaponComponent = CreateDefaultSubobject<UBFGWeaponComoponent>("WeaponComponent");
}


void ABFGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABFGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABFGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveAlong", this, &ABFGBaseCharacter::MoveAlong);
	PlayerInputComponent->BindAxis("MoveAcross", this, &ABFGBaseCharacter::MoveAcross);
	PlayerInputComponent->BindAxis("LookUp", this, &ABFGBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ABFGBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABFGBaseCharacter::JumpAction);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ABFGBaseCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ABFGBaseCharacter::StopRun);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABFGBaseCharacter::Fire);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ABFGBaseCharacter::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ABFGBaseCharacter::StopAim);
}

void ABFGBaseCharacter::MoveAlong(float Amount)
{	
	OnMovingAlong.Broadcast(Amount);
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ABFGBaseCharacter::MoveAcross(float Amount)
{
	OnMovingAcross.Broadcast(Amount);
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ABFGBaseCharacter::JumpAction()
{
	if (IsAim) return;
	OnJump.Broadcast();
	Jump();
}

void ABFGBaseCharacter::Run()
{
	IsRun = true;
}

void ABFGBaseCharacter::StopRun()
{
	IsRun = false;
}

void ABFGBaseCharacter::Fire()
{
	if (!IsAim || PlayerStats.NumberOfArrows == 0 && PlayerStats.IsArrowsLimited) return;

	WeaponComponent->Fire();
	StopAim();

	if (PlayerStats.IsArrowsLimited) 
	{
		PlayerStats.NumberOfArrows--;

		IsHaveArrows = PlayerStats.NumberOfArrows > 0;
	}
}

void ABFGBaseCharacter::Aim()
{
	if (GetCharacterMovement()->IsFalling() || !WeaponComponent->IsOwnerCanFire()) return;
	IsAim = true;
	GetWorldTimerManager().SetTimer(ChangeLevelAimTimerHandle, this, &ABFGBaseCharacter::ChangeLevelAim, TimeBetweenChangeLevelAim, true);
}

void ABFGBaseCharacter::StopAim()
{
	IsAim = false;
	CurrentLevelAim = 0;
	RightArmAimRotationZ = FVector2D{ 0.0f,0.0f };
	GetWorldTimerManager().ClearTimer(ChangeLevelAimTimerHandle);
}

void ABFGBaseCharacter::ChangeLevelAim()
{
	if (!IsAim || !GetWorld()) return;
	CurrentLevelAim = FMath::Clamp(CurrentLevelAim + ChangesInLevelAim, 0.0f, MaxLevelAim);
	RightArmAimRotationZ = FVector2D{ (CurrentLevelAim * RightArmRotationPerLevelAim), (CurrentLevelAim * (-RightArmRotationPerLevelAim))};
	if (CurrentLevelAim == MaxLevelAim || CurrentLevelAim == 0) ChangesInLevelAim = -ChangesInLevelAim;
}

void ABFGBaseCharacter::AddPoints(int32 Points)
{
	PlayerStats.NumberOfPoints = FMath::Clamp(PlayerStats.NumberOfPoints + Points, 0, PlayerStats.MaxPoints);
}