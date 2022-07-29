// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUHealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Player/STUCharacter.h"
#include "GameFramework/Controller.h"
#include "STUGameModeBase.h"
#include "Perception/AISense_Damage.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent,All,All)

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent():
bIsActivateAutoHeal(true),
HealthUpdateTime(0.3),
HealDelay(3),
HealModifier(1),
MaxHealth(100)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	GetOwner()->OnTakeAnyDamage.AddDynamic(this,&USTUHealthComponent::OnTakeAnyDamageHandle);
	GetOwner()->OnTakePointDamage.AddDynamic(this, &USTUHealthComponent::OnTakePointDamage);
	GetOwner()->OnTakeRadialDamage.AddDynamic(this, &USTUHealthComponent::OnTakeRadialDamage);

	SetHealth(MaxHealth);
	
}

bool USTUHealthComponent::TryToAddHealth(float HealthValue)
{
	if (IsHealthMax() || ISDead()) return false;
	
	SetHealth(HealthValue+Health);
	return true;
}

void USTUHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
}

void USTUHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if (IsHealthMax() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USTUHealthComponent::SetHealth(float HealthValue)
{
	const auto NextHealth = FMath::Clamp(HealthValue, 0.f, MaxHealth);
	const auto ChangeHealth = Health - NextHealth;
	Health = NextHealth;
	OnChangeHealth.Broadcast(Health, ChangeHealth);
}

bool USTUHealthComponent::IsHealthMax() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

void USTUHealthComponent::PlayCameraShake() const
{
	if (!CameraShake) return;

	if (ISDead()) return;

	const auto Char = Cast<APawn>(GetOwner());
	if (!Char) return;

	const auto Controller = Cast<APlayerController>(Char->GetController());
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void USTUHealthComponent::Killed(AController* Killer)
{
	if (!GetWorld())return;
	ASTUGameModeBase* CurrentGameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
	const auto Char = Cast<APawn>(GetOwner());
	if (CurrentGameMode && Char)
	{
		const auto CharController = Char->GetController();
		if (!CharController) return;
		CurrentGameMode->MakeKills(Killer, CharController);
	}
}

void USTUHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	TakeDamage(Damage * GetPointDamageModifier(DamagedActor, BoneName), InstigatedBy);
}

void USTUHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	TakeDamage(Damage, InstigatedBy);
}

void USTUHealthComponent::TakeDamage(float Damage, AController* InstigatedBy)
{
	if (Damage <= 0.f || ISDead() || !GetWorld())return;

	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	PlayCameraShake();

	if (ISDead())
	{
		Killed(InstigatedBy);
		OnDeath.Broadcast();
	}
	else if (bIsActivateAutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealthUpdateTime, true, HealDelay);
	}
	ReportDamageEvent(Damage, InstigatedBy);
}

float USTUHealthComponent::GetPointDamageModifier(const AActor* Actor, const FName& BoneName)
{
	const auto Char = Cast<ASTUCharacter>(Actor);
	if (!Char || !Char->GetMesh() || !Char->GetMesh()->GetBodyInstance(BoneName)) return 1.f;

	const auto PhysMaterial = Char->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
	if (!PhysMaterial || !DamageModifier.Contains(PhysMaterial))return 1.f;
	
	return DamageModifier[PhysMaterial];
}

void USTUHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
	if (!GetWorld() || !GetOwner() || !InstigatedBy->GetPawn()) return;
	UAISense_Damage::ReportDamageEvent
	(GetWorld(), GetOwner(), InstigatedBy->GetPawn(),
	Damage, InstigatedBy->GetPawn()->GetActorLocation(),
	GetOwner()->GetActorLocation());
}
