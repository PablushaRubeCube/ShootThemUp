// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/STUAmmoPickup.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LOGAmmoPickup, All, All)

bool ASTUAmmoPickup::CanGivePickup(APawn* Pawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Pawn);
	if (HealthComponent && HealthComponent->ISDead())return false;

	USTUWeaponComponent* WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Pawn);
	if (!WeaponComponent) return false;

	return WeaponComponent->TryToAddAmmo(WeaponAmmo, ClipsValue);
}
