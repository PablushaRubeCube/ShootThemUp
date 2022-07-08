// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STUBaseWeapon.h"

#include "Player/STUCharacter.h"
#include "Player/STUPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon,All,All)

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon():
MaxShotDistance(1500.f),
DefaultAmmo{30,3,true}
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponComponent"));
	SetRootComponent(WeaponMeshComponent);
}




// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMeshComponent);

	CurrentAmmo = DefaultAmmo;
	
}

void ASTUBaseWeapon::StartFireWeapon()
{
}


void ASTUBaseWeapon::StopFireWeapon()
{
}


APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
	ASTUCharacter* Char = Cast<ASTUCharacter>(GetOwner());
	if(!Char) return nullptr;
	
	return Char->GetController<APlayerController>();
}


bool ASTUBaseWeapon::GetViewPort(FVector&ViewLocation, FRotator& ViewRotator) const
{
	const ACharacter* Char = Cast<ACharacter>(GetOwner());
	if(!Char) return false;
	if (Char->IsPlayerControlled())
	{
		const APlayerController* Controller = GetPlayerController();
		if(!Controller) return false;
		{
			Controller->GetPlayerViewPoint(ViewLocation,ViewRotator);
			return true;
		}
	}
	else
	{
		return true;
	}

}


FVector ASTUBaseWeapon::GetMuzzleLocation() const
{
	return WeaponMeshComponent->GetSocketLocation(SocketName);
}


bool ASTUBaseWeapon::GetTraceData(FVector& StartTrace, FVector& EndTrace) const
{
	FVector ViewLocation;
	FRotator ViewRotator;
	if(!GetViewPort(ViewLocation,ViewRotator)) return false;
				
	StartTrace = ViewLocation;
	const FVector StartTraceDirection = ViewRotator.Vector();
	EndTrace = StartTrace + StartTraceDirection * MaxShotDistance;
	return true;
}


void ASTUBaseWeapon::MakeHit(const UWorld* World, FHitResult& HitResult,const FVector & StartTrace, const FVector & EndTrace) const
{
	if(!World) return;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());
	CollisionParameters.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult,StartTrace,EndTrace,ECollisionChannel::ECC_Visibility,CollisionParameters);
}

void ASTUBaseWeapon::DecreaseBullet()
{
	if (CurrentAmmo.Bullet == 0)
	{
		UE_LOG(LogBaseWeapon, Warning, TEXT("Clips is empty"))
	}
	CurrentAmmo.Bullet--;

	if (ClipEmpty() && !AmmoEmpty())
	{
		StopFireWeapon();
		OnReloadSignature.Broadcast(this);
	}
}

void ASTUBaseWeapon::ReloadClip()
{
	if (!CurrentAmmo.bHasInfinityAmmo)
	{
		if (CurrentAmmo.Clips == 0)
		{
			UE_LOG(LogBaseWeapon, Warning, TEXT("Dont have clips"));
				return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullet = DefaultAmmo.Bullet;
}

bool ASTUBaseWeapon::ClipEmpty() const
{
	return CurrentAmmo.Bullet == 0;
}

bool ASTUBaseWeapon::AmmoEmpty() const
{
	return !CurrentAmmo.bHasInfinityAmmo && CurrentAmmo.Clips == 0 && ClipEmpty();
}

void ASTUBaseWeapon::LogAmmoInfo()
{
	FString Log = "Bullet" + FString::FromInt(CurrentAmmo.Bullet) + " / ";
	Log += "Clips" + FString::FromInt(CurrentAmmo.Clips);

	UE_LOG(LogBaseWeapon, Warning, TEXT("%s"), *Log);
}

bool ASTUBaseWeapon::IsAmmoFull()
{
	return CurrentAmmo.Bullet == DefaultAmmo.Bullet && CurrentAmmo.Clips == DefaultAmmo.Clips;
}

bool ASTUBaseWeapon::IsWeaponCanReload()
{
	return CurrentAmmo.Bullet < DefaultAmmo.Bullet && CurrentAmmo.Clips > 0;
}

bool ASTUBaseWeapon::TryToAddAmmo(int32 Clips)
{
	if (CurrentAmmo.bHasInfinityAmmo || IsAmmoFull() || Clips <= 0) return false;

	if (AmmoEmpty())
	{
		CurrentAmmo.Clips = FMath::Clamp(Clips, 0, DefaultAmmo.Clips + 1);
		OnReloadSignature.Broadcast(this);
	}
	else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips + Clips;
		if (DefaultAmmo.Clips - NextClipsAmount >= 0)
		{
			CurrentAmmo.Clips = NextClipsAmount;
		}
		else
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullet = DefaultAmmo.Bullet;
		}
	}
	else
	{
		CurrentAmmo.Bullet = DefaultAmmo.Bullet;
	}
	return true;
}

UNiagaraComponent* ASTUBaseWeapon::SpawnMuzlleFX()
{
	if (MuzzleFX)
	{
		return	UNiagaraFunctionLibrary::SpawnSystemAttached
		(MuzzleFX, WeaponMeshComponent ,SocketName,FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::SnapToTarget,true);
	}
	return nullptr;
}




void ASTUBaseWeapon::MakeShot()
{
}

