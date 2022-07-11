// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/EnvQueryTest_CanPickup.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/STUBasePickup.h"

UEnvQueryTest_CanPickup::UEnvQueryTest_CanPickup()
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTest_CanPickup::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);

	bool WantsBeTakable = BoolValue.GetValue();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		const auto PickUp = Cast<ASTUBasePickup>(ItemActor);
		if (!PickUp) return;

		It.SetScore(TestPurpose, FilterType, PickUp->IsCanPickup(), WantsBeTakable);

	}
}
