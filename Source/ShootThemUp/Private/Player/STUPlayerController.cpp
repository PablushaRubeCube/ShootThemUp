// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STUPlayerController.h"

//test
#include "Player/STUCharacter.h"
#include "Weapon/STUBaseWeapon.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(STUPlayerController, All, All)

//test
ASTUPlayerController::ASTUPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

//test
void ASTUPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ASTUPlayerController::TestVariables()
{
	ASTUCharacter* Char = Cast<ASTUCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Char) Char->TransferTestVariables(WeaponChar, TArratWeaponChar);
}

//test
void ASTUPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(STUPlayerController, Warning, TEXT("preporty pointer %i, is valid %i"), WeaponChar != nullptr, IsValid(WeaponChar));
}
