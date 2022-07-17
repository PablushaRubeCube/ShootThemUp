// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPauseWidget : public UUserWidget
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
