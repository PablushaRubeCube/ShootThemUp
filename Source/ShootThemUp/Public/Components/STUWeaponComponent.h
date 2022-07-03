// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

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


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public://constructor
	// Sets default values for this component's properties
	USTUWeaponComponent();

private://variables

	UPROPERTY()
		ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
		TArray<ASTUBaseWeapon*> Weapons;

	UPROPERTY(EditAnywhere, Category= "Weapon", meta=(AllowPrivateAccess = "true"))
	FName SocketWeaponEquipName;

	UPROPERTY(EditAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FName SocketWeaponArmoryName;

	int32 IndexWeapon;

	//Equip animation montage
	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* EquipMontage;

	//true if we changed weapon
	bool bEquipInProgress;

	//Tarray struct weapons and reload montage
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TArray<FWeaponType> WeaponType;

	//Equip animation montage
	UPROPERTY(VisibleAnywhere, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* CurrentReloadMontage;

private://functions
	void SpawnWeapons();

	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void EquipWeapon(int32 Index);

	//functions for call anim montage
	void WeaponMontageAnimation(UAnimMontage* Montage);

	//Subscrube to anim notify STUEquipWeaponAnimNotify
	void InitialAnimation();

	//
	void OnFinishEquip(USkeletalMeshComponent* SkeletalMesh);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

public://functions
	void StartFire();
	void StopFire();
		
	void NextWeapon();

	FORCEINLINE bool IsEquipInProgress() const { return bEquipInProgress; }

	bool IsCanFire() const;

	void Reload();

};
