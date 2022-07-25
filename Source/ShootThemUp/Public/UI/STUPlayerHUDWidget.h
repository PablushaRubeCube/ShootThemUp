// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public USTUBaseWidget
{
	GENERATED_BODY()

private://variables

	UPROPERTY(EditDefaultsOnly, Category = "Color", meta = (AllowPrivateAccess = "true"))
	FLinearColor FullHealthBarColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, Category = "Color", meta = (AllowPrivateAccess = "true"))
	FLinearColor VeryLowHealthBarColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float ChangeColorThresholdHealhBar = 0.4f;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* BloodAnimation;

private://function

	UFUNCTION(BlueprintPure, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float GetHealthPrecent();

	void UpdateColorHealthBarPlayer();

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

	UFUNCTION(BlueprintPure, Category = "UI", meta = (AllowPrivateAccess = "true"))
	FString FormatBullets(int32 BulletsNum) const;

	UFUNCTION()
	class ASTUGameModeBase* GetSTUGameMode();

	void OnNewPawn(APawn* Pawn);

	void PlayBloodAnimation();

public:

	UFUNCTION(BlueprintImplementableEvent)
	void OnTakeDamage();

};
