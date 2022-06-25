// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUHealthComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent,All,All)

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent():
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

	GetOwner()->OnTakeAnyDamage.AddDynamic(this,&USTUHealthComponent::OnTakeAnyDamageHandle);
	
	Health = MaxHealth;
	OnChangeHealth.Broadcast(Health);
	
}

void USTUHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0.f || ISDead())return;

	Health = FMath::Clamp(Health - Damage,0.f,MaxHealth);
	OnChangeHealth.Broadcast(Health);
	
	if(ISDead())
	{
		OnDeath.Broadcast();
	}
}
