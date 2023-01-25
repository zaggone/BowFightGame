// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/BFGBaseWeapon.h"
#include "BFGBow.generated.h"
class ABFGArrow;
class ABFGBaseCharacter;

UCLASS()
class BOWFIGHTINGGAME_API ABFGBow : public ABFGBaseWeapon
{
	GENERATED_BODY()

public:

	ABFGBow();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Arrow")
	TSubclassOf<ABFGArrow> ArrowClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Arrow")
	float TimeToSpawnArrowAfterShot = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sockets")
	FName ArrowSocketName = "ArrowSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sockets")
	FName ArrowTipAtBowSocketName = "ArrowTipAtBowSocket";
	
	virtual void Fire() override;

protected:

	virtual void BeginPlay() override;

	virtual void MakeShot() override;

public:

	virtual void Tick(float DeltaTime) override;

	void SpawnArrow();

private:

	ABFGArrow* CurrentArrow;

	bool IsFinishSpawning;

	FTimerHandle BowTimerHandle;
};

