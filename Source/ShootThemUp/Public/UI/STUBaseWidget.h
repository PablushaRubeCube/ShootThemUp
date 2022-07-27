// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUBaseWidget : public UUserWidget
{
	GENERATED_BODY()

protected://variables

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShowAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	class USoundCue* OpenSound;

public://functinos

	void PlayShowAnimation();
	
};
