// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BFGCharacterMovementComponent.h"
#include "Player/BFGBaseCharacter.h"

float UBFGCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ABFGBaseCharacter* Player = Cast<ABFGBaseCharacter>(GetPawnOwner());
	if (Player && Player->IsAimInProgress()) {
		return MaxSpeed * AimModifier;
	}
	if (Player && Player->IsRunning()) {
		return MaxSpeed * RunModifier;
	}
	return MaxSpeed;
}
