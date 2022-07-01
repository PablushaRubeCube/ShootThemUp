// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

private://varibales

	FTimerHandle ShootTimer;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float FireRate = (0.1f);

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float BulletSpread = (1.5f);

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float DamageAmount = (10.f);

private://functions

	void MakeDamage(const FHitResult& Result);

protected://functions
	virtual void MakeShot() override;

public://functions
	virtual	void StartFireWeapon() override;
	virtual	void StopFireWeapon() override;
	

	virtual bool GetTraceData(FVector& StartTrace, FVector& EndTrace)  const override;
};
