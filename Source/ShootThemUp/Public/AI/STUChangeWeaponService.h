// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUChangeWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:

	USTUChangeWeaponService();

private://variables

	UPROPERTY(EditAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "1.0"))
	float Chance;

private://functions

	/** update next tick interval
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
