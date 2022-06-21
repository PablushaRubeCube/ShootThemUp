// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Player/STUCharacter.h"
#include "STUAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUCharacter
{
	GENERATED_BODY()

public:
    ASTUAICharacter();

private://variables
	UPROPERTY(EditDefaultsOnly, Category= "Behavior Tree", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BTAsset;
	
public://functions
	FORCEINLINE UBehaviorTree* GetBTAsset () const {return BTAsset;} 
};
