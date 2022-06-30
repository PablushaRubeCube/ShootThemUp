// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjectile.h"
#include "Kismet/GameplayStatics.h"


void ASTULauncherWeapon::MakeShot()
{
	if (!GetWorld()) return;
	if (Projectile)
	{
		const FTransform SpawnTransform(GetMuzzleLocation());
		const auto SpawnedProjectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), Projectile, SpawnTransform);
		UGameplayStatics::FinishSpawningActor(SpawnedProjectile, SpawnTransform);
	}
}


void ASTULauncherWeapon::StartFireWeapon()
{
	MakeShot();
}

//void ASTULauncherWeapon::StopFireWeapon()
//{
//}
