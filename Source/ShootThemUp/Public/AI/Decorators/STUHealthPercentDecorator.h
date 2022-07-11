// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUHealthPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:

	USTUHealthPercentDecorator();

private://variables
		UPROPERTY(EditAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
		float HealthPercent;

private://functions
/** calculates raw, core value of decorator's condition. Should not include calling IsInversed */
virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	
};
