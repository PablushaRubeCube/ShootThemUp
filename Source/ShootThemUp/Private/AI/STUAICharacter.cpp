// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUAICharacter.h"
#include "Components/STUAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjInit):
Super(ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}
	

}
