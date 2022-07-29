// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STUCharacter.h"
#include "STUHealthComponent.h"
#include "STUWeaponComponent.h"
#include "AI/STUAICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "Player/STUPlayerState.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(LogCharacter,All,All)

// Sets default values
ASTUCharacter::ASTUCharacter
(const FObjectInitializer& ObjInit):
Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName)) 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>(TEXT("HealthComponent"));

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>(TEXT("WeaponComponent"));

	LandedDamage = FVector2D(10.f, 100.f);
	LandedDamageVelocity = FVector2D(700.f, 1200.f);

	LifeSpanOnDeath = 5.f;

	ColorName = "Paint Color";
}

float ASTUCharacter::GetMovementDirection() const
{
		if (GetVelocity().IsZero()) return 0.0f;
		const auto VelocityNormal = GetVelocity().GetSafeNormal();
		const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
		const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
		const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
		return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTUCharacter::DeathChar()
{
	//PlayAnimMontage(DeathMontage);
	
	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(LifeSpanOnDeath);

	if (Controller) Controller->ChangeState(NAME_Spectating);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

	UGameplayStatics::PlaySoundAtLocation(this, PlayerDeathSound, GetActorLocation());
}

void ASTUCharacter::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (MaterialInst) MaterialInst->SetVectorParameterValue(ColorName, Color);
}

void ASTUCharacter::TurnOff()
{
	WeaponComponent->StopFire();
	WeaponComponent->Zoom(false);
	Super::TurnOff();
}

void ASTUCharacter::Reset()
{
	WeaponComponent->StopFire();
	WeaponComponent->Zoom(false);
	Super::Reset();
}

void ASTUCharacter::OnChangeHealth(float Health, float DeltaHealth)
{
}

void ASTUCharacter::OnGroudLanded(const FHitResult& Hit)
{
	const float ZVelocity = -GetCharacterMovement()->Velocity.Z;
	if (ZVelocity < LandedDamageVelocity.X) return;

	const float FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, ZVelocity);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

bool ASTUCharacter::IsRunning() const
{
	return false;
}

// Called when the game starts or when spawned
void ASTUCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(GetCharacterMovement());
	check(GetMesh());

	OnChangeHealth(HealthComponent->GetHealth(), 0.f);
	HealthComponent->OnDeath.AddUObject(this,&ASTUCharacter::DeathChar);
	HealthComponent->OnChangeHealth.AddUObject(this, &ASTUCharacter::OnChangeHealth);
	LandedDelegate.AddDynamic(this, &ASTUAICharacter::OnGroudLanded);


}

// Called every frame
void ASTUCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


