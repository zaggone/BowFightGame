// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BFGPlayerWidget.h"
#include "Player/BFGBaseCharacter.h"


float UBFGPlayerWidget::GetLevelAimPercent() const
{
	const auto Player = Cast<ABFGBaseCharacter>(GetOwningPlayerPawn());
	if (!Player) return 0.0f;

	return Player->GetLevelAimPercent();
}

FString UBFGPlayerWidget::GetArrowsData()
{
	const auto Player = Cast<ABFGBaseCharacter>(GetOwningPlayerPawn());
	if (!Player) return FString();

	auto CurrentPlayerStats = Player->GetPlayerStats();

	if (!CurrentPlayerStats.IsArrowsLimited) 
	{
		return FString("Arrows: unlimited");
	}

	return FString("Arrows : " + FString::FromInt(CurrentPlayerStats.NumberOfArrows) + " / " + FString::FromInt(CurrentPlayerStats.MaxArrows));
}

FString UBFGPlayerWidget::GetPointsData()
{
	const auto Player = Cast<ABFGBaseCharacter>(GetOwningPlayerPawn());
	if (!Player) return FString();

	auto CurrentPlayerStats = Player->GetPlayerStats();
	
	return FString("Points : " + FString::FromInt(CurrentPlayerStats.NumberOfPoints) + " / " + FString::FromInt(CurrentPlayerStats.MaxPoints));
}
