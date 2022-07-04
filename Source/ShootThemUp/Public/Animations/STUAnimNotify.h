// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STUAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifyCall, USkeletalMeshComponent*)

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

protected://functions

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

public://variables

	FOnNotifyCall OnNotifyCall;
	
};
