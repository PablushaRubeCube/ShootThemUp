// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"
#include "STUGameInstance.h"


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
	InputComponent->BindAction("MuteGame", EInputEvent::IE_Pressed, this, &ASTUPlayerController::MuteGame);
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
	if (State == EGameState::EGS_InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = (false);
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = (true);
	}
}

void ASTUPlayerController::MuteGame()
{
	if (!GetWorld()) return;
	
	const auto GameInstance = Cast<USTUGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;
	GameInstance->ToggleSoundClassVolume();
}



