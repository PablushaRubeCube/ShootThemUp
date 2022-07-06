// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/STUHealthPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LOGHeatlhPickup, All, All)

bool ASTUHealthPickup::CanGivePickup(APawn* Pawn)
{
	UE_LOG(LOGHeatlhPickup, Warning, TEXT("CharTakeHealth"))
	return true;

}
