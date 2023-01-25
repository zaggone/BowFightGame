// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BFGBaseTarget.generated.h"
UCLASS()
class BOWFIGHTINGGAME_API ABFGBaseTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	ABFGBaseTarget();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TargetMesh;

	UFUNCTION()
	void OnTargetOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:

	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Points")
	int32 TargetGivenPoints = 1.0f;

};
