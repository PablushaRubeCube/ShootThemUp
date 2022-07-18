// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "STUGameModeBase.h"
#include "STUCoreTypes.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameHUD, All, All)

void ASTUGameHUD::DrawHUD()
{
	Super::DrawHUD();

//	DrawCrossHud();
}

void ASTUGameHUD::DrawCrossHud()
{
	
	const TInterval<float> Center (Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

	const float Inded = 10.f;
	const FLinearColor ColorCross = FLinearColor::Green;
	const float Thickness = 2.f;

	DrawLine(Center.Min - Inded, Center.Max, Center.Min + Inded, Center.Max, ColorCross, Thickness);
	DrawLine(Center.Min, Center.Max - Inded, Center.Min, Center.Max + Inded, ColorCross, Thickness);
}

void ASTUGameHUD::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerHudWidget);
	check(PauseWidget);

	if (GetWorld())
	{
		GameWidgets.Add(EGameState::EGS_InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHudWidget));
		GameWidgets.Add(EGameState::EGS_Paused, CreateWidget<UUserWidget>(GetWorld(), PauseWidget));
		GameWidgets.Add(EGameState::EGS_GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidget));
		

		for (const auto Widget : GameWidgets)
		{
			const auto PairWidget = Widget.Value;
			if (!PairWidget) continue;

			PairWidget->AddToViewport();
			PairWidget->SetVisibility(ESlateVisibility::Hidden);
		}

		ASTUGameModeBase* GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnGameStateChanged.AddUObject(this, &ASTUGameHUD::GameStateChanged);
		}
	}
}

void ASTUGameHUD::GameStateChanged(EGameState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}
	
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
