#pragma once

#include "STUCoreTypes.generated.h"


//weapon
//STUWeaponComponent
USTRUCT(BlueprintType)
struct FWeaponType
{
	GENERATED_BODY()

		//Choose weapon
	UPROPERTY(EditDefaultsOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASTUBaseWeapon> WeaponClass;

	//Choose reload animation montage
	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* ReloadMontage;
};


//STUBaseWeapon
DECLARE_MULTICAST_DELEGATE(FOnReloadSignature)

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (ClampMin = "1"));
	int32 Bullet;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (EditCondition = "!bHasInfinityAmmo", ClampMin = "0"))
		int32 Clips;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		bool bHasInfinityAmmo;
};

//Health
//STUHealthComponent

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeHealthSignature, float);