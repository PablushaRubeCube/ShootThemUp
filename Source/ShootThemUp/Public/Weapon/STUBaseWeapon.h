// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	int32 Bullet;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (EditCondition = "!bHasInfinityAmmo"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	bool bHasInfinityAmmo;
};

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

protected://functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Decrase bullet when we shoot
	void DecreaseBullet();

	//call we reloaded
	void ReloadClip();

	// call to relload weapon
	bool ClipEmpty() const;

	//return true if we dont have bullet
	bool AmmoEmpty() const;

	//temp log for ammo
	void LogAmmoInfo();

public:	//functions
	virtual	void StartFireWeapon();
	virtual	void StopFireWeapon();
	virtual void MakeShot();

	APlayerController* GetPlayerController() const;
	bool GetViewPort(FVector& ViewLocation, FRotator& ViewRotator) const;
	FVector GetMuzzleLocation() const;
	virtual bool GetTraceData(FVector& StartTrace, FVector& EndTrace)  const;
	void MakeHit(const UWorld* World, FHitResult& HitResult, const FVector& StartTrace, const FVector& EndTrace) const;

};