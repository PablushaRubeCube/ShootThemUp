// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/STUEnemyEnvQueryContext.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "AISystem.h"
#include "VisualLogger/VisualLogger.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/STUAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void USTUEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	if (!QueryOwner) return;

	//ASTUAIController* Controller = Cast<ASTUAIController>(QueryOwner);
	//if (!Controller) return;
	//
	//UBlackboardComponent* BBComponent = Controller->GetBlackboardComponent();

	UBlackboardComponent* BBComponent = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if (!BBComponent) return;
	
	const auto EnemyObject = BBComponent->GetValueAsObject(EnemyKeyName);
	

	UE_CVLOG(GET_AI_CONFIG_VAR(bAllowControllersAsEQSQuerier) == false && Cast<AController>(QueryOwner) != nullptr, QueryOwner, LogEQS, Warning, TEXT("Using Controller as query's owner is dangerous since Controller's location is usually not what you expect it to be!"));
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(EnemyObject));
}