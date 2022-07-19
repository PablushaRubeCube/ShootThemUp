// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

protected:

	virtual void NativeOnInitialized() override;
	
private://variables

	UPROPERTY( meta = (BindWidget))
	class UButton* StarGameButton;
	
private://functnios

	UFUNCTION()
	void StartGame();
};
