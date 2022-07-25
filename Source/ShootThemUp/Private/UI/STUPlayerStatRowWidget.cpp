// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUPlayerStatRowWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUPlayerStatRowWidget::SetName(const FText& Name)
{
	if (!PlayerName) return;

	PlayerName->SetText(Name);
}

void USTUPlayerStatRowWidget::SetPlayerKills(const FText& Kills)
{
	if (!PlayerKills) return;

	PlayerKills->SetText(Kills);
}

void USTUPlayerStatRowWidget::SetPlayerDeaths(const FText& Death)
{
	if (!PlayerDeaths) return;

	PlayerDeaths->SetText(Death);
}

void USTUPlayerStatRowWidget::SetTeam(const FText& Team)
{
	if (!PlayerTeam) return;

	PlayerTeam->SetText(Team);
}

void USTUPlayerStatRowWidget::SetStatIndicatorVisibility(bool IsVisible)
{
	if (!PlayerStatIndicatorVisibility) return;
	PlayerStatIndicatorVisibility->SetVisibility(IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTUPlayerStatRowWidget::SetTeamColor(const FLinearColor& color)
{
	if (!TeamColor) return;
	TeamColor->SetColorAndOpacity(color);
}
