// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUHealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"


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
	if(Damage <= 0.f || ISDead() || !GetWorld())return;

	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	
	if(ISDead())
	{
		OnDeath.Broadcast();
	}
	else if (bIsActivateAutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealthUpdateTime, true, HealDelay);
	}
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
	Health = FMath::Clamp(HealthValue, 0.f, MaxHealth);
	OnChangeHealth.Broadcast(Health);
}

bool USTUHealthComponent::IsHealthMax() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}
