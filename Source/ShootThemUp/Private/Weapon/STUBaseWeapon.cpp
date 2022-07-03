// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STUBaseWeapon.h"

#include "Player/STUCharacter.h"
#include "Player/STUPlayerController.h"
#include "Kismet/GameplayStatics.h"

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
	
	GetWorld()->LineTraceSingleByChannel(HitResult,StartTrace,EndTrace,ECollisionChannel::ECC_Visibility,CollisionParameters);
}

void ASTUBaseWeapon::DecreaseBullet()
{
	CurrentAmmo.Bullet--;
	LogAmmoInfo();

	if (ClipEmpty() && !AmmoEmpty())
	{
		ReloadClip();
	}
}

void ASTUBaseWeapon::ReloadClip()
{
	UE_LOG(LogBaseWeapon, Warning, TEXT("__RELOAD__"));
	CurrentAmmo.Bullet = DefaultAmmo.Bullet;
	if (!CurrentAmmo.bHasInfinityAmmo)
	{
		CurrentAmmo.Clips--;
	}
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


void ASTUBaseWeapon::MakeShot()
{
}

