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
DECLARE_MULTICAST_DELEGATE_OneParam(FOnReloadSignature, ASTUBaseWeapon*)

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = "1"));
	int32 Bullet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (EditCondition = "!bHasInfinityAmmo", ClampMin = "0"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	bool bHasInfinityAmmo;
};

USTRUCT(BlueprintType)
struct FDataWeaponUI
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Icon");
	UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Icon");
	UTexture2D* CroshairIcon;

};

//Health
//STUHealthComponent

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeHealthSignature, float);
