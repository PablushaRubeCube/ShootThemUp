// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUAIWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUCoreTypes.h"


void USTUAIWeaponComponent::StartFire()
{
	if (IsCanFire())
	{
		if (!CurrentWeapon->AmmoEmpty())
		{
			CurrentWeapon->StartFireWeapon();
		}
		else
		{
			NextWeapon();
		}
	}
}

void USTUAIWeaponComponent::NextWeapon()
{
	if (IsEquipInProgress() || IsReloadInProgress()) return;

	IndexWeapon = (IndexWeapon + 1) % Weapons.Num();
	if (!Weapons[IndexWeapon]->AmmoEmpty())
	{
		EquipWeapon(IndexWeapon);
	}
//	EquipWeapon(IndexWeapon);
}