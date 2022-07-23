// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STULevelItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTULevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

private://variables

	UPROPERTY(meta = (BindWidget))
	class UButton* SelectLevelButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayLevelName;

	UPROPERTY(meta = (BindWidget))
	class UImage* PictureLevel;

	UPROPERTY(meta = (BindWidget))
	UImage* FramePictureLevel;

	FLevelData LevelData;

private://functions

	UFUNCTION()
	void LevelSelected();

protected:
	
	virtual void NativeOnInitialized() override;

public://variables

FOnLevelSelected OnLevelSelected;

public://functions

	void IsFrameVisible(bool IsVisible);

	void SetWidgetLevelData(const FLevelData& Data);
	FORCEINLINE FLevelData GetWidgetLevelData() const { return LevelData; }
};
