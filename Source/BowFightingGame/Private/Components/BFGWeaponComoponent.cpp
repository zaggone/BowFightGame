// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BFGWeaponComoponent.h"
#include "Weapons/BFGBaseWeapon.h"
#include "Gameframework/Character.h"
#include "Weapons/BFGArrow.h"
#include "Weapons/BFGBow.h"
#include "UserUtils.h"
#include "Kismet/GameplayStatics.h"

UBFGWeaponComoponent::UBFGWeaponComoponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UBFGWeaponComoponent::IsOwnerCanFire() const
{
	return CurrentWeapon->IsCanFire(); 
}

void UBFGWeaponComoponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
}


void UBFGWeaponComoponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBFGWeaponComoponent::Fire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->Fire();
}


void UBFGWeaponComoponent::SpawnWeapon()
{
	if (!GetWorld()) return;

	auto Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	auto Weapon = GetWorld()->SpawnActorDeferred<ABFGBaseWeapon>(WeaponClass, FTransform{}, GetOwner());
	if (!Weapon) return;
	
	Weapon->SetIsAttachedToCharacter(true);
	Weapon->FinishSpawning(FTransform{});
	UserUtils::AttachToSocket(Weapon, Character->GetMesh(), WeaponSocketName);

	CurrentWeapon = Weapon;
}

