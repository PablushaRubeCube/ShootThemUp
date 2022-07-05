// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"

float USTUPlayerHUDWidget::GetHealthPrecent()
{
	const auto Char = GetOwningPlayerPawn();
	if (!Char) return  0.0f;
	
	const auto ActorComponent = Char->GetComponentByClass(USTUHealthComponent::StaticClass());
	USTUHealthComponent* Component = Cast<USTUHealthComponent>(ActorComponent);
	if (!Component) return  0.0f;
	
	return Component->GetHealthPercentage();	
}