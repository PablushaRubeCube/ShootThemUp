// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/STUEquipWeaponAnimNotify.h"

void USTUEquipWeaponAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotifyCall.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}