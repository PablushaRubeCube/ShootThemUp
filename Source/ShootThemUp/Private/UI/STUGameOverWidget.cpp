// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (GetWorld() && GetWorld()->GetAuthGameMode())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode) GameMode->OnGameStateChanged.AddUObject(this, &USTUGameOverWidget::GameStateChanged);
    }

    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::ResetLevel);
    }
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

void USTUGameOverWidget::ResetLevel()
{
    if (!GetWorld()) return;
    const auto CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
