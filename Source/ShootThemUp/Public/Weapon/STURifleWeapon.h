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

public://functions
	virtual	void StartFireWeapon() override;
	virtual	void StopFireWeapon() override;
	virtual void MakeShot() override;

	virtual bool GetTraceData(FVector& StartTrace, FVector& EndTrace)  const override;
};