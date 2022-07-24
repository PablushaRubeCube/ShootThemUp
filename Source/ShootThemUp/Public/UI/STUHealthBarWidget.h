// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUHealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
	
	UPROPERTY(EditDefaultsOnly, Category = "Color", meta = (AllowPrivateAccess = "true"))
	FLinearColor FullHealthBarColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, Category = "Color", meta = (AllowPrivateAccess = "true"))
	FLinearColor VeryLowHealthBarColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float DisplayThresholdHealhBar = 0.8f;

	UPROPERTY(EditDefaultsOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float ChangeColorThresholdHealhBar = 0.4f;

public://functnios

	void SetHealth(float Percent);
};
