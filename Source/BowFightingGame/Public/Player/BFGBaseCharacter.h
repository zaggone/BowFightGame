// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BFGBaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovingAcrossSignature, float, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovingAlongSignature, float, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpSignature);

class UCameraComponent;
class USpringArmComponent;
class UBFGWeaponComoponent;

USTRUCT(BlueprintType)
struct FPlayerDefaultStats 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat")
	bool IsArrowsLimited = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat", meta = (EditCondition = "IsArrowsLimited"))
	int32 MaxArrows = 12;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat", meta = (EditCondition = "IsArrowsLimited"))
	int32 NumberOfArrows = MaxArrows;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat")
	int32 MaxPoints = 60;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat")
	int32 NumberOfPoints = 0;
};

UCLASS()
class BOWFIGHTINGGAME_API ABFGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ABFGBaseCharacter(const FObjectInitializer& Objinit);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBFGWeaponComoponent* WeaponComponent;

	UPROPERTY(BlueprintAssignable)
	FOnMovingAcrossSignature OnMovingAcross;

	UPROPERTY(BlueprintAssignable)
	FOnMovingAlongSignature OnMovingAlong;

	UPROPERTY(BlueprintAssignable)
	FOnJumpSignature OnJump;

protected:

	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
	bool IsRunning() const { return IsRun; };

	UFUNCTION(BlueprintCallable)
	bool IsAimInProgress() const { return IsAim; }

	UFUNCTION(BlueprintCallable)
	FVector2D GetRightArmAimRotationZ() const { return RightArmAimRotationZ; };

	UFUNCTION(BlueprintCallable)
	float GetLevelAim() const { return CurrentLevelAim; }
	float GetLevelAimPercent() const { return CurrentLevelAim/MaxLevelAim; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FPlayerDefaultStats PlayerStats;
	
	void AddPoints(int32 Points);
	
	const FPlayerDefaultStats& GetPlayerStats()  { return PlayerStats; }

	// конец игры.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHaveArrows = true;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//не менять!!!!!!!!!
	void MoveAlong(float Amount);
	void MoveAcross(float Amount);

	void JumpAction();

	void Run();
	bool IsRun = false;
	void StopRun();

	void Fire();
	void Aim();
	void StopAim();
	bool IsAim = false;
	void ChangeLevelAim();
	float CurrentLevelAim = 0.0f;
	FVector2D RightArmAimRotationZ;
	FTimerHandle ChangeLevelAimTimerHandle;	
	
	float TimeBetweenChangeLevelAim = 0.04f;
	float RightArmRotationPerLevelAim = 2.0f;
	float MaxLevelAim = 50.0f;
};
