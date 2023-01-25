// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BFGWeaponComoponent.generated.h"

class ABFGBaseWeapon;
class ABFGArrow;
class ABFGBow;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWFIGHTINGGAME_API UBFGWeaponComoponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UBFGWeaponComoponent();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf <ABFGBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sockets")
	FName WeaponSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sockets")
	FName BowStringTransformName = "BowStringTransform";

	UFUNCTION(BlueprintCallable)
	ABFGBaseWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

	bool IsOwnerCanFire() const;
		
protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Fire();

private:

	ABFGBaseWeapon* CurrentWeapon;
	void SpawnWeapon();

};
