// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHealth(float Percent)
{
	if (!HealthBar) return;
	
	bool IsHideBar = Percent > DisplayThresholdHealhBar || FMath::IsNearlyZero(Percent);
	HealthBar->SetVisibility(IsHideBar ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	HealthBar->SetFillColorAndOpacity(Percent > ChangeColorThresholdHealhBar ? FullHealthBarColor : VeryLowHealthBarColor);
	HealthBar->SetPercent(Percent);
}
