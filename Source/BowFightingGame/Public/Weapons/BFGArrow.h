// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BFGArrow.generated.h"


class UBFGArrowFlightComponent;
class ABFGBow;

UCLASS()
class BOWFIGHTINGGAME_API ABFGArrow : public AActor
{
	GENERATED_BODY()
	
public:	

	ABFGArrow();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* ArrowMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* BaseSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* CenterTransformComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* PlumTransformComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBFGArrowFlightComponent* ArrowFlightComponent;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	void SetRotationWhileAttachet();

	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetMesh() const { return ArrowMesh; }

	void SetCurrentBow(ABFGBow* Bow) { CurrentBow = Bow; }

	UFUNCTION(BlueprintCallable)
	ABFGBow* GetCurrentBow() const { return CurrentBow; }

	void MakeShot(float CurrentLevelAim);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sockets")
	FName TipSocketName = "TipSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sockets")
	FName PlumSocketName = "PlumSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Options")
	float TimeBeforeDestroy = 100.0f;

	bool IsAttachedToBow = false;

	bool OnceEventedGetPoints = false;

	bool GetIsInFlight();
	
private:

	ABFGBow* CurrentBow;

};
