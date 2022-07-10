// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUChangeWeaponService.h"
#include "Components/STUWeaponComponent.h"
#include "AIController.h"
#include "STUUtils.h"

USTUChangeWeaponService::USTUChangeWeaponService():
Chance(0.5f)
{
	NodeName = "ChangeWeapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode (OwnerComp, NodeMemory, DeltaSeconds);

	float RandomFloat = FMath::FRand();

	if (RandomFloat <= Chance && Chance > 0)
	{
		AAIController* Controller = OwnerComp.GetAIOwner();
		if (!Controller) return;
		const auto Pawn = Controller->GetPawn();
		if (!Pawn) return;

		const auto Component = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Pawn);
		if (Component)
		{
			Component->NextWeapon();
		}
	}
}
