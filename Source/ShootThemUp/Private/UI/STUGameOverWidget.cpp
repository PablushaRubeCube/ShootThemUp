// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"

bool USTUGameOverWidget::Initialize()
{
    if (GetWorld() && GetWorld()->GetAuthGameMode())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode) GameMode->OnGameStateChanged.AddUObject(this, &USTUGameOverWidget::GameStateChanged);
    }
    return Super::Initialize();
}

void USTUGameOverWidget::GameStateChanged(EGameState State)
{
    if (State == EGameState::EGS_GameOver)
    {
        UpdatePlayerStat();
    }
}

void USTUGameOverWidget::UpdatePlayerStat()
{
    if (!GetWorld() || !PlayerStateBox) return;

    PlayerStateBox->ClearChildren();

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        const auto RowWidget = CreateWidget<USTUPlayerStatRowWidget>(GetWorld(), PlayerStatRow);
        if (!RowWidget) continue;

        RowWidget->SetName(FText::FromString(*PlayerState->GetPlayerName()));
        RowWidget->SetPlayerKills(FText::FromString(FString::FromInt(PlayerState->GetKillsNum())));
        RowWidget->SetPlayerDeaths(FText::FromString(FString::FromInt(PlayerState->GetDeathNum())));
        RowWidget->SetTeam(FText::FromString(FString::FromInt(PlayerState->GetTeamID())));
        RowWidget->SetStatIndicatorVisibility(Controller->IsPlayerController());

        PlayerStateBox->AddChild(RowWidget);
    }

}
