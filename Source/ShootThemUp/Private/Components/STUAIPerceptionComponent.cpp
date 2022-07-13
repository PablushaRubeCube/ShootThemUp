// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUAIPerceptionComponent.h"

#include "AIController.h"
#include "Perception/AISense_Sight.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PerceivedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(),PerceivedActors);
	if(PerceivedActors.Num() == 0 )return nullptr;
	
	AAIController* Controller = Cast<AAIController>(GetOwner());
	if(!Controller) return nullptr;
	APawn* Char = Controller->GetPawn();
	if(!Char) return nullptr;
	
	float MaxDistance = MAX_FLT;
	AActor* ClosestActor= nullptr;
	for (const auto PerceivedActor : PerceivedActors)
	{
		const auto PerceivedPawn = Cast<APawn>(PerceivedActor);
		const bool AreEnemies = PerceivedPawn && STUUtils::AreEnemy(Controller, PerceivedPawn->GetController());

		const auto Component = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PerceivedActor);
		if (Component && !Component->ISDead() && AreEnemies)
		{
			const float CurrentDistance = (Char->GetActorLocation() - PerceivedActor->GetActorLocation()).Size();
			if (CurrentDistance < MaxDistance)
			{
				MaxDistance = CurrentDistance;
				ClosestActor = PerceivedActor;
			}
		}
	}
	return ClosestActor;
}
