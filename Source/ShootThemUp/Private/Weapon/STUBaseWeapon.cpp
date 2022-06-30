// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STUBaseWeapon.h"

#include "Player/STUCharacter.h"
#include "Player/STUPlayerController.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon,All,All)

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon():
MaxShotDistance(1500.f),
FireRate(0.1f),
BulletSpread(1.5),
DamageAmount(10.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponComponent"));
	SetRootComponent(WeaponMeshComponent);
}

void ASTUBaseWeapon::MakeDamage(const FHitResult& Result)
{
	const auto HitActor = Result.GetActor();
	if (!HitActor) return;
	HitActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}


// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMeshComponent);
	
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


void ASTUBaseWeapon::MakeShot()
{
}

