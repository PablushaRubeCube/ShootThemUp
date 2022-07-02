// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STUEquipWeaponAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifyCall, USkeletalMeshComponent*)

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUEquipWeaponAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

private://functions

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	
public://variables

	FOnNotifyCall OnNotifyCall;
};
