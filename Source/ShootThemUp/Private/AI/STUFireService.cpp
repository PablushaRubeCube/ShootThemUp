// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUFireService.h"

#include "AIController.h"
#include "STUUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUWeaponComponent.h"
#include "GameFramework/Character.h"

USTUFireService::USTUFireService()
{
	NodeName = "FireService";
}

void USTUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AAIController* Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
	//	const auto Component = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetOwner());
	//	const auto Component = Controller->GetComponentByClass(USTUWeaponComponent::StaticClass());
	//	USTUWeaponComponent* WeaponComponent = Cast<USTUWeaponComponent>(Component);
		const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent)
		{
			const UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
			bool bHasAim = BlackBoard && BlackBoard->GetValueAsObject(EnemyKey.SelectedKeyName);

			bHasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
