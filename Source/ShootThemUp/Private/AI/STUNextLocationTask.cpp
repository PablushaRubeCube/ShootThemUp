// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUNextLocationTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUNextLocationTask::USTUNextLocationTask():
Radius(1000.f),
bSelfCenter(true)
{
	NodeName = "NextLocation";
}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get controller / controller valid?
	AController* Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
	
	//get pawn/ pawn valid?
	APawn* Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
	
	//get UNavigationSystemV1 / UNavigationSystemV1 valid? / GetRandomlocation
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if(!NavSys) return EBTNodeResult::Failed;
	
	//get blackboard / blackboard valid?
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
	if(!BlackBoard) return EBTNodeResult::Failed;
	
	FVector Location = Pawn->GetActorLocation();
	if(!bSelfCenter)
	{
		 AActor* CenterActor= Cast<AActor>(BlackBoard->GetValueAsObject(CenterKey.SelectedKeyName));
		if(!CenterActor) return  EBTNodeResult::Failed;
		Location = CenterActor->GetActorLocation(); 
	}
	FNavLocation NavLocation;
	NavSys->GetRandomReachablePointInRadius(Location,Radius,NavLocation);

	//  sev random value
	BlackBoard->SetValueAsVector(AiLocationKey.SelectedKeyName,NavLocation.Location);
	return EBTNodeResult::Succeeded;
}
