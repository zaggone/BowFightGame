// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BFGBow.h"
#include "Player/BFGBaseCharacter.h"
#include "Weapons/BFGArrow.h"
#include "UserUtils.h"
#include "Player/BFGBaseCharacter.h"
#include "TimerManager.h"

ABFGBow::ABFGBow()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("BowMesh");
	SetRootComponent(WeaponMesh);
}

void ABFGBow::BeginPlay()
{
	Super::BeginPlay();
	SpawnArrow();
}

void ABFGBow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABFGBow::Fire()
{
	MakeShot();
}

void ABFGBow::MakeShot()
{
	auto CurrentCharacter = Cast<ABFGBaseCharacter>(GetOwner());
	if (!CurrentCharacter || !CurrentArrow) return;

	CurrentArrow->MakeShot(CurrentCharacter->GetLevelAim());
	CurrentArrow = nullptr;
	CanFire = false;

	if (!CurrentCharacter->IsHaveArrows) return;
	GetWorldTimerManager().SetTimer(BowTimerHandle, this, &ABFGBow::SpawnArrow, TimeToSpawnArrowAfterShot, false);
}

void ABFGBow::SpawnArrow()
{
	if (!GetWorld() || !GetIsAttachedToCharacter()) return;

	auto CurrentCharacter = Cast<ABFGBaseCharacter>(GetOwner());
	if (!CurrentCharacter->IsHaveArrows) return;

	CurrentArrow = nullptr;
	CurrentArrow = GetWorld()->SpawnActorDeferred<ABFGArrow>(ArrowClass, FTransform{});
	if (!CurrentArrow) return;

	CurrentArrow->SetOwner(GetOwner());
	CurrentArrow->IsAttachedToBow = true;
	CurrentArrow->SetCurrentBow(this);
	CurrentArrow->FinishSpawning(FTransform{});
	UserUtils::AttachToSocket(CurrentArrow, GetMesh(), ArrowSocketName);
	CanFire = true;
}
