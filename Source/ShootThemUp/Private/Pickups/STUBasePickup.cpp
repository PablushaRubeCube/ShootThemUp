// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/STUBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LOGBasePickup, All, All)

// Sets default values
ASTUBasePickup::ASTUBasePickup():
TimerRespawnPickup(5.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetSphereRadius(500.f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(SphereCollision);

}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
		
	const auto Pawn = Cast<APawn>(OtherActor);
	if (CanGivePickup(Pawn))
	{
		HidePickup();
	}
}

void ASTUBasePickup::HidePickup()
{
	if (SphereCollision)
	{
		SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		SphereCollision->SetVisibility(false, true);
		FTimerHandle TimerHande;
		GetWorldTimerManager().SetTimer(TimerHande, this, &ASTUBasePickup::RespawnPickup, TimerRespawnPickup);
	}
}

void ASTUBasePickup::RespawnPickup()
{
	if (SphereCollision)
	{
		SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		SphereCollision->SetVisibility(true, true);
	}
}

// Called when the game starts or when spawned
void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();

	check(SphereCollision);
	
}

bool ASTUBasePickup::CanGivePickup(APawn* Pawn)
{
	return false;
}

// Called every frame
void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

