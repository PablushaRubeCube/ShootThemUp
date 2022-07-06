// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickup : public ASTUBasePickup
{
	GENERATED_BODY()

private://variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Weapon", meta = (AllowPrivateAccess = "true", ClampMin = "1.0"));
	int32 ClipsValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<class ASTUBaseWeapon> WeaponAmmo;

private://functions

	virtual bool CanGivePickup(APawn* Pawn) override;


	
};
