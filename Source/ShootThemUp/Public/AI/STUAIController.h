// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/STUAIPerceptionComponent.h"
#include "STUAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController
{
	GENERATED_BODY()
public:
	ASTUAIController();

private://variables
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components", meta = (AllowPrivateAccess = "true"))
	USTUAIPerceptionComponent* STUPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "AI", meta = (AllowPrivateAccess = "true"))
	FName FocusOnKeyName;

private://functions
	
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	AActor*  GetFocusOnActor();
	
};
