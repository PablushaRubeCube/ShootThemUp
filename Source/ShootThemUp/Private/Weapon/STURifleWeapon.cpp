// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STURifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "Player/STUCharacter.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogRifleWeapon, All, All)

ASTURifleWeapon::ASTURifleWeapon():
FireRate(0.1f),
BulletSpread(1.5f),
DamageAmount(10.f),
TraceEndName("TraceEnd")
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
	InitilizationFX();
	GetWorldTimerManager().SetTimer(ShootTimer, this, &ASTURifleWeapon::MakeShot, FireRate, true);
	MakeShot();
}

void ASTURifleWeapon::StopFireWeapon()
{
	GetWorldTimerManager().ClearTimer(ShootTimer);
	SetVisibilityFX(false);
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
		FXComponent->PlayImpactFX(HitResult);
	}
	DecreaseBullet();
	SpawnTraceFX(GetMuzzleLocation(), EndTrace);
	//InitilizationFX();
	//UE_LOG(LogRifleWeapon, Display, TEXT("MakeShot"));
}

void ASTURifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(FXComponent);
}

void ASTURifleWeapon::InitilizationFX()
{
	if (!RifleMuzzleFX)
	{
		RifleMuzzleFX = SpawnMuzlleFX();
	}
	SetVisibilityFX(true);
}

void ASTURifleWeapon::SetVisibilityFX(bool IsVisible)
{
	if (RifleMuzzleFX)
	{
		RifleMuzzleFX->SetPaused(!IsVisible);
		RifleMuzzleFX->SetVisibility(IsVisible, false);
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

void ASTURifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;

	const auto Component = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFx, TraceStart);
	if (Component)
	{
		Component->SetNiagaraVariableVec3(TraceEndName, TraceEnd);
	}
}