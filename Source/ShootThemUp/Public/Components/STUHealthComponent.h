// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeHealthSignature, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

private://varibales

	float Health;

	//Activate autoheal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	bool bIsActivateAutoHeal;

	//Timer for AutoHeal
	FTimerHandle HealTimerHandle;

	//rate of auto heal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true", EditCondition = "bIsActivateAutoHeal"))
	float HealthUpdateTime;

	//Delay for timer autoHeal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true", EditCondition = "bIsActivateAutoHeal"))
	float HealDelay;

	//Value of Autoheal player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true", EditCondition = "bIsActivateAutoHeal"))
	float HealModifier;

private://functions

	UFUNCTION()
	void OnTakeAnyDamageHandle( AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

	//regeneration health character
	void HealUpdate();

	//Set Health and call Broadcast
	void SetHealth(float HealthValue);

protected://variables
	
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = "0"))
	float MaxHealth;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public://Variables
	
	FOnDeathSignature OnDeath;

	FOnChangeHealthSignature OnChangeHealth;

public://functions
	FORCEINLINE int32 GetHealth()const {return Health;}

	FORCEINLINE bool ISDead() const {return FMath::IsNearlyZero(Health); }
};
