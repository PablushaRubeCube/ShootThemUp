// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjectile.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


void ASTULauncherWeapon::MakeShot()
{
	if (!GetWorld()) return;
	if( AmmoEmpty())
	{
		UGameplayStatics::PlaySound2D(GetWorld(), AmmoEmptySound);
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

	const auto EndPoit = HitResult.bBlockingHit ? HitResult.ImpactPoint : EndTrace;
	const auto Direction = (EndPoit - GetMuzzleLocation()).GetSafeNormal();
	
	//DrawDebugLine(GetWorld(), GetMuzzleLocation(), EndPoit, FColor::Red, false, 3.f, 0, 3.f);
	
	if (Projectile)
	{
		const FTransform SpawnTransform(GetMuzzleLocation());
		ASTUProjectile* SpawnedProjectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(Projectile,SpawnTransform);
		if (SpawnedProjectile)
		{
			SpawnedProjectile->SetOwner(GetOwner());
			SpawnedProjectile->SetDirectionProjectile(Direction);
			SpawnedProjectile->FinishSpawning(SpawnTransform);
		}
	}
	DecreaseBullet();
	SpawnMuzlleFX();
	UGameplayStatics::PlaySound2D(GetWorld(), ShootSound);
}


void ASTULauncherWeapon::StartFireWeapon()
{
	MakeShot();
}

//void ASTULauncherWeapon::StopFireWeapon()
//{
//}
