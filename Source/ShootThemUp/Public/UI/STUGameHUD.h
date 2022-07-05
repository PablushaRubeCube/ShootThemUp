// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
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

private://functions

	virtual void DrawHUD()override;

	void DrawCrossHud();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	
};
