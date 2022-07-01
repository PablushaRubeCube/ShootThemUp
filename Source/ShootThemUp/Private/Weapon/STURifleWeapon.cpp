// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STURifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "Player/STUCharacter.h"

void ASTURifleWeapon::MakeDamage(const FHitResult& Result)
{
	const auto HitActor = Result.GetActor();
	if (!HitActor) return;
	HitActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}

void ASTURifleWeapon::StartFireWeapon()
{
	MakeShot();
	GetWorldTimerManager().SetTimer(ShootTimer, this, &ASTURifleWeapon::MakeShot, FireRate, true);
}

void ASTURifleWeapon::StopFireWeapon()
{
	GetWorldTimerManager().ClearTimer(ShootTimer);
}

void ASTURifleWeapon::MakeShot()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FVector StartTrace;
		FVector EndTrace;
		if (!GetTraceData(StartTrace, EndTrace))return;

		FHitResult HitResult;
		MakeHit(World, HitResult, StartTrace, EndTrace);

		if (HitResult.bBlockingHit)
		{
			ASTUCharacter* HitChar = Cast<ASTUCharacter>(HitResult.Actor);
			if (HitChar)
			{
				MakeDamage(HitResult);
			}
			DrawDebugSphere(World, HitResult.ImpactPoint, 3.f, 10, FColor::Red, false, 3.f, 0.f, 3.f);
			DrawDebugLine(World, GetMuzzleLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.f, 0, 3.f);
		}
		else
		{
			DrawDebugLine(World, GetMuzzleLocation(), EndTrace, FColor::Red, false, 3.f, 0, 3.f);
		}
	}
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