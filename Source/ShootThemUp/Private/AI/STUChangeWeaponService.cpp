// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUChangeWeaponService.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
	NodeName = "ChangeWeapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode (OwnerComp, NodeMemory, DeltaSeconds);

	float RandomFloat = FMath::FRand();

	//Chance/

	AController* Controller = Cast<AController>(OwnerComp.GetAIOwner());
	if (!Controller) return;
	APawn* Pawn = Controller->GetPawn();
	if(!Pawn) return;

	const auto Component = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Pawn);
	if (Component)
	{
		Component->NextWeapon();
	}
}
