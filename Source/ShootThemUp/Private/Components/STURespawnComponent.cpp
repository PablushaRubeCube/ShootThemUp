// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"

// Sets default values for this component's properties
USTURespawnComponent::USTURespawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void USTURespawnComponent::UpdateRespawn()
{
	if (--TimeCountDown == 0)
	{
		if (!GetWorld())return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimer);
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode) GameMode->Respawn(Cast<AController>(GetOwner()));
	}
}

// Called when the game starts
void USTURespawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USTURespawnComponent::StartTimerRespawn(int32& RespawnTime)
{
	if (!GetWorld())return;
	TimeCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimer, this, &USTURespawnComponent::UpdateRespawn, 1.f,true);
}

bool USTURespawnComponent::IsRespawnInProgress()
{
	if(!GetWorld()) return false;
	return GetWorld()->GetTimerManager().IsTimerActive(RespawnTimer);
}


//// Called every frame
//void USTURespawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

