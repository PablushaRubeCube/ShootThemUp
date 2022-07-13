// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerState, All, All)

void ASTUPlayerState::GetInfo()
{
	UE_LOG(LogPlayerState, Display, TEXT("Team ID: %i, Kills: %i, Dealth: %i"), GetTeamID(), GetKillsNum(), GetDeathNum());
}
