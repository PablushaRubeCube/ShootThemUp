// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUCoreTypes.h"
#include "STUPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASTUPlayerController();

private://variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USTURespawnComponent* RespawnComponent;

private:// functions

	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent() override;

	void PauseGame();

	virtual void BeginPlay() override;

	void GameStateChanged(EGameState State);

	void MuteGame();

};
