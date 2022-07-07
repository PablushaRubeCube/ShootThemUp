// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Player/STUCharacter.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

DEFINE_LOG_CATEGORY_STATIC(STUProjectile, All, All)

// Sets default values
ASTUProjectile::ASTUProjectile():
LifeSpan(5.f),
Damage(50.f),
Radius(200.f),
bDoFullDamage(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionSphere->SetSphereRadius(5.f);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionSphere->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionSphere);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileComponent->InitialSpeed = (2000.f);

	FXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>(TEXT("FXComponent"));

}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld())return;

	ProjectileComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(), Damage, GetActorLocation(), Radius, UDamageType::StaticClass(),{GetOwner()}, this, GetPawnController(), bDoFullDamage);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 26.f, FColor::Red, false, 3.f, 0.f, 3.f);
	FXComponent->PlayImpactFX(Hit);

	Destroy();
}

AController* ASTUProjectile::GetPawnController()
{
	ASTUCharacter* Char = Cast<ASTUCharacter>(GetOwner());
	return Char ? Char->GetController() : nullptr;
}

// Called when the game starts or when spawned
void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(ProjectileComponent);
	check(CollisionSphere);
	check(FXComponent);

	ProjectileComponent->Velocity = DirectionProjectile * ProjectileComponent->InitialSpeed;
	CollisionSphere->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionSphere->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
	SetLifeSpan(LifeSpan);
}


