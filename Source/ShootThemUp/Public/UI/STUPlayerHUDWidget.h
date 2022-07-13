// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

private://function

	UFUNCTION(BlueprintPure, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float GetHealthPrecent();

	UFUNCTION(BlueprintCallable, Category = "UI", meta = (AllowPrivateAccess = "true"))
	bool GetCurrentWeaponUIData(FDataWeaponUI& UIData) const;

	UFUNCTION(BlueprintCallable, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	bool GetCurrentWeaponAmmoData(FAmmoWeapon& AmmoData) const;

	UFUNCTION(BlueprintPure, Category = "Player", meta = (AllowPrivateAccess = "true"))
	bool PlayerIsAlive() const;

	UFUNCTION(BlueprintPure, Category = "Player", meta = (AllowPrivateAccess = "true"))
	bool PlayerIsSpectator() const;

	virtual bool Initialize() override;

	void OnHealthChanged(float Health, float DeltaHealth);

	UFUNCTION(BlueprintPure, Category = "statistics", meta = (AllowPrivateAccess = "true"))
	void GetTimeRound(int32& Minute, int32& Seconds);

	UFUNCTION(BlueprintPure, Category = "statistics", meta = (AllowPrivateAccess = "true"))
	void GetCurrentRound(int32& CurrentRound, int32& RoundsNum);

	UFUNCTION(BlueprintPure, Category = "statistics", meta = (AllowPrivateAccess = "true"))
	int32 GetKills();

	UFUNCTION()
	class ASTUGameModeBase* GetSTUGameMode();

public:

	UFUNCTION(BlueprintImplementableEvent)
	void OnTakeDamage();

};
