// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BFGBaseWeapon.h"


ABFGBaseWeapon::ABFGBaseWeapon()
{

	PrimaryActorTick.bCanEverTick = true;

}


void ABFGBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABFGBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

