// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStatRowWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerStatRowWidget : public UUserWidget
{
	GENERATED_BODY()

private://variables

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerKills;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerDeaths;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerTeam;

	UPROPERTY(meta = (BindWidget))
	class UImage* PlayerStatIndicatorVisibility;
	
public://functions

	void SetName(const FText& Name);
	void SetPlayerKills(const FText& Kills);
	void SetPlayerDeaths(const FText& Death);
	void SetTeam(const FText& Team);
	void SetStatIndicatorVisibility(bool IsVisible);
};
