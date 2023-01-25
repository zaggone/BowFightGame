// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BFGArrowFlightComponent.generated.h"

class ABFGArrow;
class ABFGBow;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWFIGHTINGGAME_API UBFGArrowFlightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UBFGArrowFlightComponent();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartFlight(float CurrentLevelAim);

	void StopFlight();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	FVector AccelOfGravity = { 0.0f, 0.0f, -980.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	FVector WindVelocityVector = { 30.0f, -30.0f, 0.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MaxVelocity = 10000.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	FVector2D RangeInitialVelocity {5000.0f, 10000.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	bool IsRotateWhileFlight = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "IsRotateWhileFlight"))
	FName CenterComponentName;

	UFUNCTION(BlueprintCallable)
	bool GetIsInFlight() const { return IsInFlight; }

private:

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	FVector GetShotDirection(float& _InitialVelocity);

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	void GetDistanceToHittedBody(float& _CurrentDistance, const FVector& TraceStart, const FVector& TraceEnd);

	APlayerController* GetPlayerController() const;

	void SetRotationWhileFlight(FVector VelocityLocation);

	FVector GetAccel(float Height, FVector _CurrentVelocityVector);

	FVector2D RangeLevelAim{ 0, 50 };

	ABFGArrow* CurrentArrow;

	USceneComponent* CurrentCenterTransformComponent;
	
	FVector CurrentCenterLocation;

	FVector CurrentInitialVelocityVector;

	FVector CurrentInitialLocation;
	
	FVector CurrentVelocityVector;

	bool IsInFlight = false;
};
