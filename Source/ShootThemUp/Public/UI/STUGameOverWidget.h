// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STUGameOverWidget.generated.h"


/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public USTUBaseWidget
{
	GENERATED_BODY()

private://Variables

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* PlayerStateBox;

	UPROPERTY(EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf <UUserWidget> PlayerStatRow;

	UPROPERTY(meta = (BindWidget))
	class UButton* ResetLevelButton;

private://functions

	virtual void NativeOnInitialized() override;

	void GameStateChanged(EGameState State);

	void UpdatePlayerStat();

	UFUNCTION()
	void ResetLevel();
	
};
