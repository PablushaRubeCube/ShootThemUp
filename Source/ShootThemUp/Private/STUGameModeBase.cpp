// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameModeBase.h"

#include "Player/STUCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHud.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameMode, All, All)

ASTUGameModeBase::ASTUGameModeBase()
{
	DefaultPawnClass = ASTUCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	StartRound();
	CurrentRound = 1;
}

void ASTUGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = (ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	for (int32 i = 0; i < GameModeData.PlayersNum - 1; ++i)
	{
		const auto SpawnedController = GetWorld()->SpawnActor<AAIController>(AIController, SpawnParameters);
		RestartPlayer(SpawnedController);
	}
	
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		 if(PawnToSpawn) return PawnToSpawn;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTUGameModeBase::StartRound()
{
	GetWorldTimerManager().SetTimer
	(TimerRoundTimeComeDown, this, &ASTUGameModeBase::RoundTimeComeDown, 1.0f, true);
	CurrentTime = GameModeData.TimerComeDown;
}

void ASTUGameModeBase::RoundTimeComeDown()
{
	UE_LOG(LogSTUGameMode, Display, TEXT("Time: %i / Round: %i/%i"), CurrentTime, CurrentRound, GameModeData.Rounds);
	if(--CurrentTime <= 0 )
	{
		GetWorldTimerManager().ClearTimer(TimerRoundTimeComeDown);
		if (CurrentRound + 1 <= GameModeData.Rounds)
		{
			++CurrentRound;
			StartRound();
			ResetPlayer();
		}
		else
		{
			UE_LOG(LogSTUGameMode, Warning, TEXT("GameOver"))
		}
	}
}

void ASTUGameModeBase::ResetPlayer()
{
	if (!GetWorld()) return;
	
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void ASTUGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Destroy();
		RestartPlayer(Controller);
	}
}


