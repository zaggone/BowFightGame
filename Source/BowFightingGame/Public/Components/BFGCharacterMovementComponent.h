// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BFGCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BOWFIGHTINGGAME_API UBFGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.1", ClampMax = "5.0"))
	float RunModifier = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.1", ClampMax = "1.1"))
	float AimModifier = 0.4f;

	virtual float GetMaxSpeed() const override;
	
};
