// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUPauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPauseWidget : public USTUBaseWidget
{
	GENERATED_BODY()

private://variables
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ClearPauseButton;

private://functnios

	virtual bool Initialize() override;

	UFUNCTION()
	void ContinueGame();
	
};
