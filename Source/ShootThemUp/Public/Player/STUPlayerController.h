// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	//test
	ASTUPlayerController();

	//test
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//test
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//test
	UPROPERTY()
	class ASTUBaseWeapon* WeaponChar;
	
	//test
	UPROPERTY()
		TArray<ASTUBaseWeapon*> TArratWeaponChar;

	//test
	UFUNCTION(BlueprintCallable)
	void TestVariables();
};
