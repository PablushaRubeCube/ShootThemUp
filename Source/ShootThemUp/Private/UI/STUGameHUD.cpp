// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void ASTUGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHud();
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

	auto Widget = CreateWidget<UUserWidget>(GetWorld(), PlayerHudWidget);
	if (Widget)
	{
		Widget->AddToViewport();
	}

}
