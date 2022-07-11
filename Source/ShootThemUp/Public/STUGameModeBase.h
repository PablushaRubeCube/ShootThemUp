// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUCoreTypes.h"
#include "STUGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUGameModeBase();

private://variables

	//store gamemode variables
	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FGameModeData GameModeData;

	//Set controller to spawn when game start
	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AController> AIController;

	//Set pawn to spawn when game start
	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APawn> PawnToSpawn;


	int32 CurrentRound;
	int32 CurrentTime;
	FTimerHandle TimerRoundTimeComeDown;

private://functions

// Call funtions when StartPlay
virtual void StartPlay()override;

//Spawn Bots
void SpawnBots();

//Return AICharacter when controller AI
virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

//Start round when we start play and start next round if we done previous
void StartRound();

// time counter round
void RoundTimeComeDown();

//Reset Player after end round
void ResetPlayer();

//reset one player
void ResetOnePlayer(AController* Controller);

void CreateInfoTeam();

FLinearColor DetermineColorByTeamID(const int32& ID);

void SetPlayerColor(AController* Controller);
	
};
