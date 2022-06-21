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
	if(!Controller) return;
		
	const auto Component = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Cast<ACharacter>(Controller->GetOwner()));

	if(Component)
	{
		const UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
		bool bHasAim = BlackBoard && BlackBoard->GetValueAsObject(EnemyKey.SelectedKeyName);

		bHasAim ? Component->StartFire() : Component->StopFire();
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
