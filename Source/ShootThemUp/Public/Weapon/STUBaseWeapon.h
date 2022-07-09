// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"




UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASTUBaseWeapon();


private://Variables

	FAmmoWeapon CurrentAmmo;

protected://variables

	//skeletal mesh our weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float MaxShotDistance;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName SocketName = "MuzzleFlashSocket";

	//skeletal mesh our weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FAmmoWeapon DefaultAmmo;

	//SetIcons for weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Icon")
	FDataWeaponUI DataWeaponUI;

	//Set Muzzle Flash
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Icon")
	class UNiagaraSystem* MuzzleFX;



protected://functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Decrase bullet when we shoot
	void DecreaseBullet();

	// call to relload weapon
	bool ClipEmpty() const;

	//temp log for ammo
	void LogAmmoInfo();

	bool IsAmmoFull();

	//Spawn choose Muzzle
	class UNiagaraComponent* SpawnMuzlleFX();

public:	//functions
	virtual	void StartFireWeapon();
	virtual	void StopFireWeapon();
	virtual void MakeShot();

	//return true if we dont have bullet
	bool AmmoEmpty() const;

	APlayerController* GetPlayerController() const;
	bool GetViewPort(FVector& ViewLocation, FRotator& ViewRotator) const;
	FVector GetMuzzleLocation() const;
	virtual bool GetTraceData(FVector& StartTrace, FVector& EndTrace)  const;
	void MakeHit(const UWorld* World, FHitResult& HitResult, const FVector& StartTrace, const FVector& EndTrace) const;

	//Call when we need reload
	FOnReloadSignature OnReloadSignature;

	//call we reloaded
	void ReloadClip();

	bool IsWeaponCanReload();

	//Return Icons Data
	FORCEINLINE FDataWeaponUI GetDataWeaponUI() const { return DataWeaponUI; }

	//Return Bullets and clips data
	FORCEINLINE FAmmoWeapon GetDataWeaponAmmo() const { return CurrentAmmo; }

	bool TryToAddAmmo(int32 Clips);

};