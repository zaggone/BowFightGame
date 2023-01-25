// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BFGBaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class BOWFIGHTINGGAME_API ABFGBaseHUD : public AHUD
{
	GENERATED_BODY()
	
		void DrawHUD();

	void BeginPlay();

	void DrowCrossHair();

};
