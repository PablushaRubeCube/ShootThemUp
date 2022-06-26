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
	ASTUCharacter();
//	ASTUCharacter(const FObjectInitializer& ObjInit);

private://variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Components", meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Components", meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Components", meta=(AllowPrivateAccess = "true"))
	class USTUHealthComponent* HealthComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Component", meta=(AllowPrivateAccess = "true"))
	class USTUWeaponComponent* WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Component", meta=(AllowPrivateAccess = "true"))
	class UTextRenderComponent* HealthTextComponent;
	
	//UPROPERTY(BlueprintReadOnly, Category= "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsRun;

	//UPROPERTY(BlueprintReadOnly, Category= "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsMoveForward;

	//Montage for death animation
	UPROPERTY(EditAnywhere, Category= "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DeathMontage;

	// Landing range damage
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector2D LandedDamage;

	// Landing range velocity
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector2D LandedDamageVelocity;

private://functions
	
	void MoveForward(float Value);
	void MoveRight(float Value);

	void Run();
	void StopRun();

	UFUNCTION(BlueprintPure, Category= "Movement",meta = (AllowPrivateAccess = "true"))
	float GetMovementDirection() const;

	void DeathChar();

	void OnChangeHealth(float Health);

	//call when we landed
	UFUNCTION()
	void OnGroudLanded(const FHitResult& Hit);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	// functions

	UFUNCTION(BlueprintCallable, Category="Movement")
	bool IsRunning() const;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};


