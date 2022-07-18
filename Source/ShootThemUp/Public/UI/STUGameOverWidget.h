// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUGameOverWidget.generated.h"


/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

private://Variables

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* PlayerStateBox;

	UPROPERTY(EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf <UUserWidget> PlayerStatRow;

private://functions

	virtual bool Initialize() override;

	void GameStateChanged(EGameState State);

	void UpdatePlayerStat();
	
};
