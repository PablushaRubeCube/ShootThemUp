// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STUNextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USTUNextLocationTask();

private://variables
	UPROPERTY(EditAnywhere, Category="Location", meta = (AllowPrivateAccess = "true"))
	float Radius;

	UPROPERTY(EditAnywhere, Category= "Location", meta=(AllowPrivateAccess = "true"));
	FBlackboardKeySelector AiLocationKey;

	UPROPERTY(EditAnywhere, Category= "AI", meta=(AllowPrivateAccess = "true"))
	bool bSelfCenter;

	UPROPERTY(EditAnywhere, Category= "AI", meta=(AllowPrivateAccess = "true", EditCondition = "!SelfCenter"));
	FBlackboardKeySelector CenterKey;

private://functions
	/** starts this task, should return Succeeded, Failed or InProgress
 *  (use FinishLatentTask() when returning InProgress)
 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
