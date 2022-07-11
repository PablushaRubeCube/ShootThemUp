// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/STUAmmoDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUAIWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"

USTUAmmoDecorator::USTUAmmoDecorator()
{
	NodeName = "NeedAmmo?";
}
bool USTUAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto Component = STUUtils::GetSTUPlayerComponent<USTUAIWeaponComponent>(Controller->GetPawn());
	if (!Component) return false;

	return Component->NeedAmmo(Weapon);
	
	return false;
}
