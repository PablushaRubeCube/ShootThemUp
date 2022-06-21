// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUWeaponComponent.h"

#include "Player/STUCharacter.h"

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent():
SocketName("WeaponPoint")
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

SpawnWeapon();
	
}

void USTUWeaponComponent::SpawnWeapon()
{
	UWorld* World = GetWorld();
	if (World)
	{
		ASTUCharacter* Char = Cast<ASTUCharacter>(GetOwner());
		if(Char)
		{
			if(WeaponClass)
			{
				 CurrentWeapon= World->SpawnActor<ASTUBaseWeapon>(WeaponClass);
				if(CurrentWeapon)
				{
					const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
					CurrentWeapon->AttachToComponent(Char->GetMesh(),AttachmentTransformRules,SocketName);
					CurrentWeapon->SetOwner(Char);
				}
			}
		}
	}
}

void USTUWeaponComponent::StartFire()
{
	if(CurrentWeapon)
	{
		CurrentWeapon->StartFireWeapon();
	}
}

void USTUWeaponComponent::StopFire()
{
	if(CurrentWeapon)
	{
		CurrentWeapon->StopFireWeapon();
	}
}
