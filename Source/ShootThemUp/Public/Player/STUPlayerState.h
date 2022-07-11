// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
	GENERATED_BODY()

private://variables

	int32 TeamID;

	FLinearColor TeamColor;

public://functions/

	FORCEINLINE int32 GetTeamID() const { return TeamID; }
	FORCEINLINE void SetTeamID(const int32& ID) { TeamID = ID;}

	FORCEINLINE FLinearColor GetTeamColor() const { return TeamColor; }
	FORCEINLINE void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
	
};
