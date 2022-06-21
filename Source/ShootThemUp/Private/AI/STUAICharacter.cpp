// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUAICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

ASTUAICharacter::ASTUAICharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}
	

}
