// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

private://Variables
	
	//class to spawn when we shot 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<class ASTUProjectile> Projectile;

	UPROPERTY(EditAnywhere, Category = "Sound", meta = (AllowPrivateAccess = "true"));
	class USoundCue* AmmoEmptySound;

protected://functions

	virtual void MakeShot() override;

public://functnios

	virtual	void StartFireWeapon() override;
	//virtual	void StopFireWeapon() override;
	
	
};
