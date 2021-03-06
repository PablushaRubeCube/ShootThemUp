// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameModeBase.h"

#include "Player/STUCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHud.h"
#include "AIController.h"
#include "Player/STUPlayerState.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"
#include "Components/STUWeaponComponent.h"
#include "EngineUtils.h"



DEFINE_LOG_CATEGORY_STATIC(LogSTUGameMode, All, All)

constexpr static int32 MinTimeRoundToRespawn = 10;

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
	SetGameState(EGameState::EGS_InProgress);
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
			GameOver();
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
		Controller->GetPawn()->Reset();
	}
		RestartPlayer(Controller);
		SetPlayerColor(Controller);
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
		PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
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

bool ASTUGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const bool bCanPause = Super::SetPause(PC, CanUnpauseDelegate);

	if (bCanPause)
	{
		SetGameState(EGameState::EGS_Paused);
	}
	return bCanPause;
}

bool ASTUGameModeBase::ClearPause()
{
	const bool bCanClearStatus = Super::ClearPause();

	if (bCanClearStatus)
	{
		SetGameState(EGameState::EGS_InProgress);
	}

	return bCanClearStatus;
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
	CallRespawn(VictimController);
}

void ASTUGameModeBase::Respawn(AController* Controller)
{
	ResetOnePlayer(Controller);
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

void ASTUGameModeBase::CallRespawn(AController* Controller)
{
	const bool RespawnAvaliable = CurrentTime > MinTimeRoundToRespawn + GameModeData.RespawnTime;
	if (RespawnAvaliable)
	{
		if (!Controller) return;
		const auto RespawnComponent = STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(Controller);
		if (!RespawnComponent) return;
		RespawnComponent->StartTimerRespawn(GameModeData.RespawnTime);
	}	
}

void ASTUGameModeBase::GameOver()
{
	for (auto pawn : TActorRange<APawn>(GetWorld()))
	{
		pawn->TurnOff();
		pawn->DisableInput(nullptr);
	}
	UE_LOG(LogSTUGameMode, Warning, TEXT("GameOver"))
	GetIfnoPlayersState();
	SetGameState(EGameState::EGS_GameOver);


}

void ASTUGameModeBase::SetGameState(EGameState State)
{
	if (GameModeState == State)return;

	GameModeState = State;
	OnGameStateChanged.Broadcast(State);
}

void ASTUGameModeBase::StopAllFire()
{
	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		USTUWeaponComponent* Component = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Pawn);
		if (!Component) continue;

		Component->StopFire();
		Component->Zoom(false);
	}
}


