// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUFindEnemyService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUAIPerceptionComponent.h"
#include "Perception/AIPerceptionComponent.h"

USTUFindEnemyService::USTUFindEnemyService()
{
	NodeName = "Serching Enemy";
}

/** update next tick interval
 * this function should be considered as const (don't modify state of object) if node is not instanced! */
 void USTUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
		UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
		if(BlackBoard)
		{
			AAIController* AIController = OwnerComp.GetAIOwner();
			if(AIController)
			{
				USTUAIPerceptionComponent* PerceptionComponent = Cast<USTUAIPerceptionComponent>(AIController->GetAIPerceptionComponent());
				if(	PerceptionComponent)
				{
					BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName,PerceptionComponent->GetClosestEnemy());
				}
			}
		}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}