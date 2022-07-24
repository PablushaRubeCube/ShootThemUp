// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUCharacter.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	//ASTUCharacter();
	ASTUCharacter(const FObjectInitializer& ObjInit);

private://variables

	//Montage for death animation
	UPROPERTY(EditAnywhere, Category= "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float LifeSpanOnDeath;

	// Landing range damage
	UPROPERTY(EditAnywhere, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	FVector2D LandedDamage;

	// Landing range velocity
	UPROPERTY(EditAnywhere, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	FVector2D LandedDamageVelocity;

	UPROPERTY(EditAnywhere, Category = "Color", meta = (AllowPrivateAccess = "true"))
	FName ColorName;

private://functions

	UFUNCTION(BlueprintPure, Category= "Movement",meta = (AllowPrivateAccess = "true"))
	float GetMovementDirection() const;

	//call when we landed
	UFUNCTION()
	void OnGroudLanded(const FHitResult& Hit);

protected://variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class USTUHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		class USTUWeaponComponent* WeaponComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnChangeHealth(float Health, float DeltaHealth);

public:	// functions

	UFUNCTION(BlueprintCallable, Category="Movement")
	virtual bool IsRunning() const;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DeathChar();

	void SetPlayerColor(const FLinearColor& Color);

};


