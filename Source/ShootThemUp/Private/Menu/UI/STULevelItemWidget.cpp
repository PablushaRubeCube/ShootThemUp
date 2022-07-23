// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/STULevelItemWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "STUCoreTypes.h"

void USTULevelItemWidget::LevelSelected()
{
	OnLevelSelected.Broadcast(LevelData);
}

void USTULevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (SelectLevelButton)
	{
		SelectLevelButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::LevelSelected);
	}
}

void USTULevelItemWidget::IsFrameVisible(bool IsVisible)
{
	if (FramePictureLevel)
	{
		FramePictureLevel->SetVisibility(IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void USTULevelItemWidget::SetWidgetLevelData(const FLevelData& Data)
{
	LevelData = Data;

	if (PictureLevel)
	{
		PictureLevel->SetBrushFromTexture(LevelData.LevelPicture);
	}
	if (DisplayLevelName)
	{
		DisplayLevelName->SetText(FText::FromName(LevelData.DisplayName));
	}
}
