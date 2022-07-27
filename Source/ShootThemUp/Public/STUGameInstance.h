// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCoreTypes.h"
#include "STUGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

private://variables

	UPROPERTY(EditDefaultsOnly, Category = "Level", meta = (AllowPrivateAccess  = "true"))
	TArray <FLevelData> Levels;

	UPROPERTY(EditDefaultsOnly,Category = "Level", meta = (AllowPrivateAccess = "true"))
	FLevelData SelectedLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Level", meta = (AllowPrivateAccess = "true"))
	FName MainMenuName = NAME_None;

public://functions
	FORCEINLINE const TArray<FLevelData>& GetLevels() const { return Levels; }

	FORCEINLINE FLevelData GetSelectedLevel() const { return SelectedLevel; }
	FORCEINLINE void SetSelectedLevel(const FLevelData& Data) { SelectedLevel = Data; }

	FORCEINLINE FName GetMainMenuName() const { return MainMenuName; }
};
