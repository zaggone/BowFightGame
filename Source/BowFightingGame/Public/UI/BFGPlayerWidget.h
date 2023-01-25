// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BFGPlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOWFIGHTINGGAME_API UBFGPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetLevelAimPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	FString GetArrowsData();

	UFUNCTION(BlueprintCallable, Category = "UI")
	FString GetPointsData();

};
