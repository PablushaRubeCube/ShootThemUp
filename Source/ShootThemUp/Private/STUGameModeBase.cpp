// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameModeBase.h"

#include "Player/STUCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHud.h"
#include "AIController.h"
#include "Player/STUPlayerState.h"


DEFINE_LOG_CATEGORY_STATIC(LogSTUGameMode, All, All)

ASTUGameModeBase::ASTUGameModeBase()
{
	DefaultPawnClass = ASTUCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
	PlayerStateClass = ASTUPlayerState::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateInfoTeam();
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
				GetIfnoPlayersState();
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
		SetPlayerColor(Controller);
	}
}

void ASTUGameModeBase::CreateInfoTeam()
{
	if (!GetWorld()) return;

	int32 CurrentTeamID = 1;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = (It->Get());
		if (!Controller) continue;

		const auto PlayerState = (Controller->GetPlayerState<ASTUPlayerState>());
	//	const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamID(CurrentTeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(CurrentTeamID));

		SetPlayerColor(Controller);

		CurrentTeamID = CurrentTeamID == 1 ? 2 : 1;
	}
}

FLinearColor ASTUGameModeBase::DetermineColorByTeamID(const int32& ID)
{
	if (ID - 1 < GameModeData.TeamsColor.Num())
	{
		return GameModeData.TeamsColor[ID - 1];
	}

	UE_LOG(LogGameMode, Warning, TEXT("ArrayIndex %i > TeamCollor.Num()% , Set DefaultColor"), (ID - 1), GameModeData.TeamsColor.Num());
	return GameModeData.DefaultColor;
}

void ASTUGameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller) return;

	const auto PlayerState = (Controller->GetPlayerState<ASTUPlayerState>());
	if (!PlayerState) return;

	const auto Char = Cast<ASTUCharacter>(Controller->GetPawn());
	if (!Char) return;

	Char->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASTUGameModeBase::MakeKills(AController* KillerController, AController* VictimController)
{
	if (!KillerController && !VictimController)return;

	const auto KillerState = KillerController->GetPlayerState<ASTUPlayerState>();
	const auto VictimState = VictimController->GetPlayerState<ASTUPlayerState>();

	if (KillerState)
	{
		KillerState->AddKill();
	}
	if (VictimState)
	{
		VictimState->AddDeath();
	}
}

void ASTUGameModeBase::GetIfnoPlayersState()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		if (It)
		{
			const auto Controller = It->Get();
			if (Controller)
			{
			const auto	playerState  = Controller->GetPlayerState<ASTUPlayerState>();
			playerState->GetInfo();
			}
		}
	}
}


