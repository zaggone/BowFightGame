// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/BFGBaseTarget.h"
#include "Components/BoxComponent.h"
#include "Weapons/BFGArrow.h"
#include "Player/BFGBaseCharacter.h"


ABFGBaseTarget::ABFGBaseTarget()
{

	PrimaryActorTick.bCanEverTick = false;
	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>("TargetMesh");

}

void ABFGBaseTarget::BeginPlay()
{
	Super::BeginPlay();
	TargetMesh->OnComponentBeginOverlap.AddDynamic(this, &ABFGBaseTarget::OnTargetOverlap);
}

void ABFGBaseTarget::OnTargetOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto CurrentArrow = Cast<ABFGArrow>(OtherActor);
	if (CurrentArrow && !CurrentArrow->OnceEventedGetPoints && !CurrentArrow->IsAttachedToBow && CurrentArrow->GetOwner())
	{
		auto CurrentCharacter = Cast<ABFGBaseCharacter>(CurrentArrow->GetOwner());
		if (CurrentCharacter) 
		{
			CurrentCharacter->AddPoints(TargetGivenPoints);
		}
	}
}

