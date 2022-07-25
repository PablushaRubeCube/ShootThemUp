// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/STUMenuHUD.h"
#include "UI/STUBaseWidget.h"

void ASTUMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if(GetWorld() && ToSpawnMainMenu)
	{
		const auto Widget = CreateWidget<USTUBaseWidget>(GetWorld(), ToSpawnMainMenu);
		if (Widget)
		{
			Widget->AddToViewport();
			Widget->PlayShowAnimation();
		}
	}
}
