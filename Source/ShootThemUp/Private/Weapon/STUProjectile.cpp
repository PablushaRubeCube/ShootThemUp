// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"

// Sets default values
ASTUProjectile::ASTUProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionSphere->SetSphereRadius(5.f);
	SetRootComponent(CollisionSphere);
}

// Called when the game starts or when spawned
void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


