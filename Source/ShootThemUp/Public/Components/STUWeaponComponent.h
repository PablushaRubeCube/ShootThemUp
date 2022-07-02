// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public://constructor
	// Sets default values for this component's properties
	USTUWeaponComponent();

private://variables

	UPROPERTY(EditAnywhere, Category= Weapon, meta=(AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class ASTUBaseWeapon>> WeaponClasses;



	UPROPERTY(EditAnywhere, Category= "Weapon", meta=(AllowPrivateAccess = "true"))
	FName SocketWeaponEquipName;

	UPROPERTY(EditAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FName SocketWeaponArmoryName;

	int32 IndexWeapon;

private://functions
	void SpawnWeapons();

	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void EquipWeapon(int32 Index);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

public://functions
	void StartFire();
	void StopFire();
		
	void NextWeapon();


	UPROPERTY()
		ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
		TArray<ASTUBaseWeapon*> Weapons;
};
