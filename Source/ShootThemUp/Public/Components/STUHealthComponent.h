// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeHealth,float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

private://varibales

	float Health;

private://functions
	UFUNCTION()
void OnTakeAnyDamageHandle( AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

protected://variables
	
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = "0"))
	float MaxHealth;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public://Variables
	
	FOnDeath OnDeath;

	FOnChangeHealth OnChangeHealth;

public://functions
	FORCEINLINE int32 GetHealth()const {return Health;}

	FORCEINLINE bool ISDead() const {return Health <= 0;}
};
