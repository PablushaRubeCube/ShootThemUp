// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUCoreTypes.h"
#include "STUUtils.h"
#include "STUGameModeBase.h"
#include "STUCoreTypes.h"
#include "Player/STUPlayerState.h"
#include "Player/STUCharacter.h"
#include "Components/ProgressBar.h"


float USTUPlayerHUDWidget::GetHealthPrecent()
{	
	USTUHealthComponent* Component = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	if (!Component) return  0.0f;
	
	return Component->GetHealthPercentage();	
}

void USTUPlayerHUDWidget::UpdateColorHealthBarPlayer()
{
	if (HealthBar)
	{
		HealthBar->SetFillColorAndOpacity
		(GetHealthPrecent() > ChangeColorThresholdHealhBar ? FullHealthBarColor : VeryLowHealthBarColor);
	}
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FDataWeaponUI& UIData) const
{
	USTUWeaponComponent* WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentDataWeaponUI(UIData);
}

bool USTUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoWeapon& AmmoData) const
{
	USTUWeaponComponent* WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentDataAmmo(AmmoData);
}

bool USTUPlayerHUDWidget::PlayerIsAlive() const
{
	USTUHealthComponent* Component = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	return Component && !Component->ISDead();
}

bool USTUPlayerHUDWidget::PlayerIsSpectator() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->StateName == NAME_Spectating;
}

bool USTUPlayerHUDWidget::Initialize()
{
	if (GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}
	return Super::Initialize();
}

void USTUPlayerHUDWidget::OnHealthChanged(float Health, float DeltaHealth)
{
	if (DeltaHealth > 0)
	{
		OnTakeDamage();
		PlayBloodAnimation();
	}
	UpdateColorHealthBarPlayer();
}

void USTUPlayerHUDWidget::GetTimeRound(int32& Minute, int32& Seconds)
{
	if (!GetSTUGameMode())return;
	 Minute = (GetSTUGameMode()->GetCurrentTime() / 60);
	 Seconds = (GetSTUGameMode()->GetCurrentTime() % 60);
}

void USTUPlayerHUDWidget::GetCurrentRound(int32& CurrentRound, int32& RoundsNum)
{
	if (!GetSTUGameMode())return;
	CurrentRound = (GetSTUGameMode()->GetCurrentRound());
	RoundsNum = (GetSTUGameMode()->GetGameModeData().Rounds);
}

int32 USTUPlayerHUDWidget::GetKills()
{
	if (!GetOwningPlayer())return 0;
	//const auto PlayerState = Cast<ASTUPlayerState> (GetOwningPlayer()->PlayerState);
	const auto	PlayerState = GetOwningPlayer()->GetPlayerState<ASTUPlayerState>();
	if (!PlayerState)return 0;
	//UE_LOG(LogTemp, Display, TEXT("Kills:%s"), *PlayerState->GetName());

	return	PlayerState->GetKillsNum();

}

FString USTUPlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
	const int32 MaxLen = 2;
	const TCHAR PrefixSymbol = '0';

	FString BulletStr = FString::FromInt(BulletsNum);
	const int32 SymbolsNumToAdd = MaxLen - BulletStr.Len();

	if (SymbolsNumToAdd > 0)
	{
		BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
	}

	return BulletStr;
}

ASTUGameModeBase* USTUPlayerHUDWidget::GetSTUGameMode()
{
	if (!GetWorld()) return nullptr;

	const auto CurrentGameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
	return CurrentGameMode ? CurrentGameMode : nullptr;
}

void USTUPlayerHUDWidget::OnNewPawn(APawn* Pawn)
{
	USTUHealthComponent* Component = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Pawn);
	if (Component)
	{
		Component->OnChangeHealth.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
	}
	UpdateColorHealthBarPlayer();
}

void USTUPlayerHUDWidget::PlayBloodAnimation()
{
	if (!IsAnimationPlaying(BloodAnimation))
	{
		PlayAnimation(BloodAnimation);
	}
}


