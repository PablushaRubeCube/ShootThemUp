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

public:

	ASTURifleWeapon();

private://varibales

	FTimerHandle ShootTimer;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float FireRate;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float BulletSpread;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float DamageAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FX", meta = (AllowPrivateAccess = "true"))
	class USTUWeaponFXComponent* FXComponent;

private://functions

	void MakeDamage(const FHitResult& Result);

protected://functions
	virtual void MakeShot() override;

	virtual void BeginPlay() override;

public://functions
	virtual	void StartFireWeapon() override;
	virtual	void StopFireWeapon() override;
	

	virtual bool GetTraceData(FVector& StartTrace, FVector& EndTrace)  const override;
};
