// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BFGArrowFlightComponent.h"
#include "Weapons/BFGArrow.h"
#include "Weapons/BFGBow.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"

float TimeBeforeShot;
UBFGArrowFlightComponent::UBFGArrowFlightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentArrow = Cast<ABFGArrow>(GetOwner());
}


void UBFGArrowFlightComponent::BeginPlay()
{
	Super::BeginPlay();
	check(CurrentArrow); // класс стрелы обязателен!!!

	if (IsRotateWhileFlight)
	{
		CurrentCenterTransformComponent = Cast<USceneComponent>(CurrentArrow->GetDefaultSubobjectByName(CenterComponentName)); //ошибка при касте (либо не указан обьект либо он не scene component)
		check(CurrentCenterTransformComponent);
	}
}

void UBFGArrowFlightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
				
	if (IsInFlight && GetWorld())
	{

		float CurrentTime = GetWorld()->GetTimeSeconds() - TimeBeforeShot; //время
		FVector CurrentAccelVector = GetAccel(CurrentArrow->GetActorLocation().Z / 100.0f, CurrentVelocityVector);
		FVector ChangeLocation = CurrentInitialLocation + (CurrentInitialVelocityVector + CurrentAccelVector * 0.5f * CurrentTime) * CurrentTime; //перемещение

		CurrentArrow->SetActorLocation(ChangeLocation);
		CurrentVelocityVector = CurrentInitialVelocityVector + CurrentAccelVector * CurrentTime; //вектор скорости 

		if (IsRotateWhileFlight) 
		{
			SetRotationWhileFlight(CurrentVelocityVector);
		}
	}			
}



void UBFGArrowFlightComponent::StartFlight(float CurrentLevelAim)
{
	if (!GetWorld() || IsInFlight) return;

	float InitialVelocity = FMath::GetMappedRangeValueClamped(RangeLevelAim, RangeInitialVelocity, CurrentLevelAim);

	FVector ShotDirection = GetShotDirection(InitialVelocity);
	CurrentVelocityVector = CurrentInitialVelocityVector = ShotDirection * InitialVelocity;
	CurrentInitialLocation = CurrentArrow->GetActorLocation();

	TimeBeforeShot = GetWorld()->GetTimeSeconds();
	IsInFlight = true;
}

void UBFGArrowFlightComponent::StopFlight()
{
	if (!GetWorld()) return;
	IsInFlight = false;
}
			
void UBFGArrowFlightComponent::SetRotationWhileFlight(FVector VelocityLocation)
{
	if (!GetWorld() && !IsRotateWhileFlight) return;
	FVector CenterTransformComponentLocation = CurrentCenterTransformComponent->GetComponentLocation();
	FVector VelocityLocationByCenter = CurrentCenterTransformComponent->GetComponentLocation() + VelocityLocation;
	auto CurrentRotation = UKismetMathLibrary::FindLookAtRotation(CenterTransformComponentLocation, VelocityLocationByCenter);
	CurrentCenterTransformComponent->SetWorldRotation(CurrentRotation);
}

FVector UBFGArrowFlightComponent::GetAccel(float Height, FVector _CurrentVelocityVector)
{
	return AccelOfGravity - FMath::Exp(-Height / 10000) * AccelOfGravity.Size() * (_CurrentVelocityVector - WindVelocityVector) * (_CurrentVelocityVector - WindVelocityVector).Size() / (MaxVelocity * MaxVelocity);
}

APlayerController* UBFGArrowFlightComponent::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(CurrentArrow->GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool UBFGArrowFlightComponent::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

void UBFGArrowFlightComponent::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(CurrentArrow->GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
}

void UBFGArrowFlightComponent::GetDistanceToHittedBody(float& _CurrentDistance, const FVector& TraceStart, const FVector& TraceEnd)
{
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	if (HitResult.bBlockingHit) 
	{
		_CurrentDistance = HitResult.Distance;
	}
}

FVector UBFGArrowFlightComponent::GetShotDirection(float& _InitialVelocity) 
{
	float CurrentDistance = _InitialVelocity;

	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotation);

	float Hypotenuse = FVector::Distance(PlayerViewLocation, CurrentArrow->GetActorLocation());
	FVector HypotenuseVector = CurrentArrow->GetActorLocation() - PlayerViewLocation;
	float ForwardDistance = FVector::DotProduct(HypotenuseVector.GetSafeNormal(), PlayerViewRotation.Vector()) * Hypotenuse;
	FVector TraceStartLocation = PlayerViewLocation + PlayerViewRotation.Vector() * ForwardDistance;
	FVector TraceEndLocation = PlayerViewLocation + PlayerViewRotation.Vector() * ForwardDistance + PlayerViewRotation.Vector() * _InitialVelocity;

	GetDistanceToHittedBody(CurrentDistance, TraceStartLocation, TraceEndLocation);

	return (PlayerViewLocation + PlayerViewRotation.Vector() * ForwardDistance + PlayerViewRotation.Vector() * CurrentDistance - CurrentArrow->GetActorLocation()).GetSafeNormal();
}