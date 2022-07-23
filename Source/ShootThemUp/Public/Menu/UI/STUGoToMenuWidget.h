// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGoToMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private://variables

	UPROPERTY(meta = (BindWidget))
	class UButton* GoToMenuButton;

private://functnios

	UFUNCTION()
	void GoToMainMenu();

protected://functions

	virtual void NativeOnInitialized() override;
	
};
