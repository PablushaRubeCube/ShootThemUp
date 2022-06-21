// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUCharacterMovementComponent.h"

#include "STUCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
	 const float MaxSpeed = Super::GetMaxSpeed();

	ASTUCharacter* Player = Cast<ASTUCharacter>(GetPawnOwner());
	return Player && Player->IsRunning()? MaxSpeed * RunModifier : MaxSpeed;
	
}
