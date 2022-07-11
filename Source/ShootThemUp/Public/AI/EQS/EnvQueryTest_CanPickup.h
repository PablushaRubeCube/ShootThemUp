// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_CanPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_CanPickup : public UEnvQueryTest
{
	GENERATED_BODY()

public:

	UEnvQueryTest_CanPickup();

private:

	/** Function that does the actual work */
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	
};
