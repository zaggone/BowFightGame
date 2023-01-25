// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BFGArrow.h"
#include "Player/BFGBaseCharacter.h"
#include "Weapons/BFGBow.h"
#include "Components/BFGArrowFlightComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABFGArrow::ABFGArrow()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BaseSceneComponent = CreateDefaultSubobject<USceneComponent>("BaseSceneComponent");
	SetRootComponent(BaseSceneComponent);
	
	PlumTransformComponent = CreateDefaultSubobject<USceneComponent>("ThirdSceneComponent");
	PlumTransformComponent->SetupAttachment(BaseSceneComponent);

	CenterTransformComponent = CreateDefaultSubobject<USceneComponent>("CenterTransformComponent");
	CenterTransformComponent->SetupAttachment(PlumTransformComponent);
	
	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>("ArrowMesh");
	ArrowMesh->SetupAttachment(CenterTransformComponent);

	ArrowFlightComponent = CreateDefaultSubobject<UBFGArrowFlightComponent>("ArrowFlightComponent");
}

void ABFGArrow::BeginPlay()
{
	Super::BeginPlay();

	check(ArrowFlightComponent); 

	OnActorBeginOverlap.AddDynamic(this, &ABFGArrow::OnOverlap);
}

void ABFGArrow::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{	
	if (IsAttachedToBow || !GetOwner() || !GetWorld()) return;

	if (OtherActor == GetOwner()) 
	{
		return;
	};
	
	ArrowFlightComponent->StopFlight();
}

void ABFGArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsAttachedToBow) 
	{
		SetRotationWhileAttachet();
	}

	if (GetActorLocation().Z < -1000.0f) Destroy();
}

void ABFGArrow::MakeShot(float CurrentLevelAim)
{
	FDetachmentTransformRules DetachmentTransformRule{ EDetachmentRule::KeepWorld, false };
	DetachFromActor(DetachmentTransformRule);
	IsAttachedToBow = false;
	CurrentBow = nullptr;
	ArrowFlightComponent->StartFlight(CurrentLevelAim);
	SetLifeSpan(TimeBeforeDestroy);
}

bool ABFGArrow::GetIsInFlight()
{
	return ArrowFlightComponent->GetIsInFlight();
}
		

void ABFGArrow::SetRotationWhileAttachet()
{
	FVector ArrowTipAtBowSocketLocation = CurrentBow->GetMesh()->GetSocketLocation(CurrentBow->ArrowTipAtBowSocketName);
	FVector PlumTransformComponentLocation = PlumTransformComponent->GetComponentLocation();

	auto CurrentRotation = UKismetMathLibrary::FindLookAtRotation(PlumTransformComponentLocation, ArrowTipAtBowSocketLocation);
	PlumTransformComponent->SetWorldRotation(CurrentRotation);
}
