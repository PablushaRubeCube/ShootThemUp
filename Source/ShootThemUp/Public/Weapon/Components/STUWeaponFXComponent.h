// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUWeaponFXComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponFXComponent();

private://variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX", meta=(AllowPrivateAccess = "true"))
	FImpactData DefaultImpact;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX", meta = (AllowPrivateAccess = "true"))
	TMap<class UPhysicalMaterial*, FImpactData> DataEffectsMap;

//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//public:	//functions
//	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	//functions
	//Call when we shoot
	void PlayImpactFX(const FHitResult& Hit);

		
};
