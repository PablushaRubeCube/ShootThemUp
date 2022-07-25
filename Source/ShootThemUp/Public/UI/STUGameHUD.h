// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUCoreTypes.h"
#include "STUGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
	GENERATED_BODY()

private://variables

	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> PlayerHudWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> PauseWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> GameOverWidget;

	UPROPERTY()
	TMap<EGameState,class USTUBaseWidget*> GameWidgets;

	UPROPERTY()
	USTUBaseWidget* CurrentWidget;

private://functions

	virtual void DrawHUD()override;

	void DrawCrossHud();

	void GameStateChanged(EGameState State);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	
};
