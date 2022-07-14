// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUSpectatorWidget.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"

bool USTUSpectatorWidget::GetRespawnTime(int32& time)
{
	const auto Component = STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(GetOwningPlayer());
	if (!Component || !Component->IsRespawnInProgress()) return false;
	
	time = Component->GetTimeCountDown();
	return true;
}