// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BFGBaseWeapon.generated.h"

UCLASS()
class BOWFIGHTINGGAME_API ABFGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABFGBaseWeapon();
	
	virtual void Fire(){};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UMeshComponent* WeaponMesh;

	UFUNCTION(BlueprintCallable)
	UMeshComponent* GetMesh() const { return WeaponMesh; }

	void SetIsAttachedToCharacter(bool State) { IsAttachedToCharacter = State; }
	bool GetIsAttachedToCharacter() { return IsAttachedToCharacter; }
	
	virtual bool IsCanFire() { return CanFire; }

protected:

	virtual void BeginPlay() override;
	
	virtual void MakeShot(){};

	FName MuzzleSocketName = "MuzzleSocket";

	bool CanFire = false;

public:	
	
	virtual void Tick(float DeltaTime) override;

private:

	bool IsAttachedToCharacter = false;
};
