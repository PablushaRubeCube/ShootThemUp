// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
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

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitGameButton;

	//Box for Array Level
	UPROPERTY( meta = (BindWidget))
	class UHorizontalBox* LevelBox;

	UPROPERTY(EditDefaultsOnly, Category = "Level", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ToSpawnLevelWidget;

	TArray<class USTULevelItemWidget*> LevelWidets;
	
private://functnios

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();

	void InitialLevels();

public:
	UFUNCTION()
	void Selectlevel(const FLevelData & Data);
};
