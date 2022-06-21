// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUAIController.h"

#include "AI/STUAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

ASTUAIController::ASTUAIController():
FocusOnKeyName ("EnemyActor")
{
	STUPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SetPerceptionComponent(*STUPerceptionComponent);
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ASTUAICharacter* Char = Cast<ASTUAICharacter>(InPawn);
	if(Char)
	{
		RunBehaviorTree(Char->GetBTAsset());
	}
}

void ASTUAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto Enemy = GetFocusOnActor();
	SetFocus(Enemy);
}

AActor* ASTUAIController::GetFocusOnActor()
{
	if(!GetBlackboardComponent()) return nullptr;
	return Cast <AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
