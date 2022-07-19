// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUMenuHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

private://variables

	UPROPERTY(EditAnywhere, category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf <class UUserWidget> ToSpawnMainMenu;
	
};
