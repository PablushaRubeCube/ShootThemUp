// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUCharacter.h"
#include "STUAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUCharacter
{
	GENERATED_BODY()

public://constructor
    ASTUAICharacter(const FObjectInitializer& ObjInit);

private://variables
	UPROPERTY(EditDefaultsOnly, Category= "Behavior Tree", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BTAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* HealthWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	float DistanceDrawHealhtWidget;
	
private://functnios

	void UpdateHealthWidgetVisibility();

protected://functnios

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnChangeHealth(float Health, float DeltaHealth) override;


public://functions
	FORCEINLINE UBehaviorTree* GetBTAsset () const {return BTAsset;} 

	virtual void DeathChar() override;
};
