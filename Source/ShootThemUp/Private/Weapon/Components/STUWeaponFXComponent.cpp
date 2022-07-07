// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
//void USTUWeaponFXComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//	
//}


//// Called every frame
//void USTUWeaponFXComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	//niagara
	if (!GetWorld()) return;
	auto DataImpact = DefaultImpact;
	if (Hit.PhysMaterial.IsValid())
	{
		auto Material = Hit.PhysMaterial.Get();
		if (DataEffectsMap.Contains(Material))
		{
			DataImpact = DataEffectsMap[Material];
		}
	}
	UNiagaraFunctionLibrary::SpawnSystemAtLocation
	(GetWorld(), DataImpact.NiagaraEffect, Hit.Location, Hit.ImpactNormal.Rotation());

	//Decal
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation
	(GetWorld(), DataImpact.Decal.Material, DataImpact.Decal.Size, Hit.Location, Hit.ImpactNormal.Rotation());
	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(DataImpact.Decal.LifeTime, DataImpact.Decal.FadeOutTime);
	}
}

