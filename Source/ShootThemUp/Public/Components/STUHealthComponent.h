// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"


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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX", meta = (AllowPrivateAccess = "true"))
	TSubclassOf <UCameraShakeBase> CameraShake;

	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	TMap<class UPhysicalMaterial*,float> DamageModifier;
	
private://functions

	UFUNCTION()
	void OnTakeAnyDamageHandle( AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

	//regeneration health character
	void HealUpdate();

	//Set Health and call Broadcast
	void SetHealth(float HealthValue);

	bool IsHealthMax() const;

	void PlayCameraShake() const;

	//Call when we was kill
	void Killed(AController* Killer);

	UFUNCTION()
	void OnTakePointDamage
	(AActor* DamagedActor, float Damage, class AController* InstigatedBy,
	FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName,
	FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

	UFUNCTION()
	void OnTakeRadialDamage
	(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

	void TakeDamage(float Damage, class AController* InstigatedBy);

	float GetPointDamageModifier(const AActor* Actor, const FName& BoneName);

	void ReportDamageEvent(float Damage, AController* InstigatedBy);

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

	//return percent of health in for widget
	FORCEINLINE float GetHealthPercentage() const { return Health / MaxHealth; }

	bool TryToAddHealth(float HealthValue);


};
