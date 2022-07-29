// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public://constructor
	// Sets default values for this component's properties
	USTUWeaponComponent();

private://variables

	UPROPERTY(EditAnywhere, Category= "Weapon", meta=(AllowPrivateAccess = "true"))
	FName SocketWeaponEquipName;

	UPROPERTY(EditAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FName SocketWeaponArmoryName;

	//Equip animation montage
	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* EquipMontage;

	//true if we changed weapon
	UPROPERTY(VisibleAnywhere, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	bool bEquipInProgress;

	//true if we changed weapon
	UPROPERTY(VisibleAnywhere, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	bool bReloadInProgress;

	//Equip animation montage
	UPROPERTY(VisibleAnywhere, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* CurrentReloadMontage;


protected://variables

	//Tarray struct weapons and reload montage
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TArray<FWeaponType> WeaponType;

	UPROPERTY()
	class ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBaseWeapon*> Weapons;

	int32 IndexWeapon;

private://functions

	void SpawnWeapons();

	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);



	//functions for call anim montage
	void WeaponMontageAnimation(UAnimMontage* Montage);

	//Subscrube to anim notify STUEquipWeaponAnimNotify
	void InitialAnimation();

	//
	void OnFinishEquip(USkeletalMeshComponent* SkeletalMesh);

	void OnFinishReload(USkeletalMeshComponent* SkeletalMesh);

	//Call when we want change clip
	void ChangeClip();

	//call automaticly when we dont have bullets in clip
	void ClipIsEmpty(ASTUBaseWeapon* AmmoEmptyWeapon);

protected:// functions

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	void EquipWeapon(int32 Index);

public://functions
	virtual void StartFire();

	void StopFire();
		
	virtual void NextWeapon();

	FORCEINLINE bool IsEquipInProgress() const { return bEquipInProgress; }

	FORCEINLINE bool IsReloadInProgress() const { return bReloadInProgress; }

	bool IsCanFire() const;

	bool IsCanReload() const;

	void Reload();

	//Return Current Icon Data
	bool GetCurrentDataWeaponUI(FDataWeaponUI& Data) const;

	//Return Current Ammo Data
	bool GetCurrentDataAmmo(FAmmoWeapon& Data) const;

	bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> Weapon, int32 Clips);

	bool NeedAmmo(TSubclassOf<ASTUBaseWeapon>Weapon);

	void Zoom(const bool bIsZoom);

};

