// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASTUProjectile::ASTUProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionSphere->SetSphereRadius(5.f);
	SetRootComponent(CollisionSphere);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileComponent->InitialSpeed = (2000.f);

}

// Called when the game starts or when spawned
void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(ProjectileComponent);
	
	ProjectileComponent->Velocity = DirectionProjectile * ProjectileComponent->InitialSpeed;
	SetLifeSpan(5.f);
}


