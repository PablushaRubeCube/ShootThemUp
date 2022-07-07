// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/STUHealthPickup.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LOGHeatlhPickup, All, All)

bool ASTUHealthPickup::CanGivePickup(APawn* Pawn)
{
	USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Pawn);
	
	if (HealthComponent && HealthComponent->ISDead()) return false;

	return HealthComponent && HealthComponent->TryToAddHealth(HealthAmount);

}
