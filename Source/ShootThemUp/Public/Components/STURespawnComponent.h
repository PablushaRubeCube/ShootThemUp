// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTURespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTURespawnComponent();

private://variables

	FTimerHandle RespawnTimer;
	int32 TimeCountDown;

private://functnios

	void UpdateRespawn();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public://functions
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartTimerRespawn(int32& RespawnTime);

	FORCEINLINE int32 GetTimeCountDown() const { return TimeCountDown; }
	bool IsRespawnInProgress();
		
};
