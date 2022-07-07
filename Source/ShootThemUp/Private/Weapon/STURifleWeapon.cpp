// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STURifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "Player/STUCharacter.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

ASTURifleWeapon::ASTURifleWeapon():
FireRate(0.1f),
BulletSpread(1.5f),
DamageAmount(10.f)
{
	FXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>(TEXT("FXComponent"));
}

void ASTURifleWeapon::MakeDamage(const FHitResult& Result)
{
	const auto HitActor = Result.GetActor();
	if (!HitActor) return;
	HitActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}

void ASTURifleWeapon::StartFireWeapon()
{
	GetWorldTimerManager().SetTimer(ShootTimer, this, &ASTURifleWeapon::MakeShot, FireRate, true);
	MakeShot();
}

void ASTURifleWeapon::StopFireWeapon()
{
	GetWorldTimerManager().ClearTimer(ShootTimer);
}

void ASTURifleWeapon::MakeShot()
{
	if (!GetWorld() || AmmoEmpty())
	{
		StopFireWeapon();
		return;
	}
	
	FVector StartTrace;
	FVector EndTrace;
	if (!GetTraceData(StartTrace, EndTrace))
	{
		StopFireWeapon();
		return;
	}
	FHitResult HitResult;
	MakeHit(GetWorld(), HitResult, StartTrace, EndTrace);

	if (HitResult.bBlockingHit)
	{
		ASTUCharacter* HitChar = Cast<ASTUCharacter>(HitResult.Actor);
		if (HitChar)
		{
			MakeDamage(HitResult);
		}
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 3.f, 10, FColor::Red, false, 3.f, 0.f, 3.f);
		//DrawDebugLine(GetWorld(), GetMuzzleLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.f, 0, 3.f);
		FXComponent->PlayImpactFX(HitResult);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleLocation(), EndTrace, FColor::Red, false, 3.f, 0, 3.f);
	}
	
	DecreaseBullet();
}

void ASTURifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(FXComponent);
}

bool ASTURifleWeapon::GetTraceData(FVector& StartTrace, FVector& EndTrace) const
{
	FVector ViewLocation;
	FRotator ViewRotator;
	if (!GetViewPort(ViewLocation, ViewRotator)) return false;

	StartTrace = ViewLocation;
	const float HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector StartTraceDirection = FMath::VRandCone(ViewRotator.Vector(), HalfRad);
	EndTrace = StartTrace + StartTraceDirection * MaxShotDistance;
	return true;
}