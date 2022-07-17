// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"


DEFINE_LOG_CATEGORY_STATIC(STUPlayerController, All, All)

ASTUPlayerController::ASTUPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>(TEXT("RespawnComponent"));
}

void ASTUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("PauseGame", EInputEvent::IE_Pressed, this, &ASTUPlayerController::PauseGame);

}

void ASTUPlayerController::PauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASTUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) GameMode->OnGameStateChanged.AddUObject(this, &ASTUPlayerController::GameStateChanged);

}

void ASTUPlayerController::GameStateChanged(EGameState State)
{
	switch (State)
	{
	case EGameState::EGS_WaintingToStart:
		break;
	case EGameState::EGS_InProgress:
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = (false);
		break;
	case EGameState::EGS_GameOver:
		break;
	case EGameState::EGS_Paused:
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = (true);
		break;
	case EGameState::EGS_Max:
		break;
	default:
		break;
	}
}



