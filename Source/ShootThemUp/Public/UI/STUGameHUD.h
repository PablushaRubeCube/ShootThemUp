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

	UPROPERTY()
	TMap<EGameState, UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* CurrentWidget;

private://functions

	virtual void DrawHUD()override;

	void DrawCrossHud();

	void GameStateChanged(EGameState State);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	
};
