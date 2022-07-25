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

void USTULevelItemWidget::HoverLevel()
{
	if (FramePictureLevel)
	{
		FramePictureLevel->SetVisibility( ESlateVisibility::Visible);
	}
}

void USTULevelItemWidget::UnhoverLevel()
{
	if (FramePictureLevel)
	{
		FramePictureLevel->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USTULevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (SelectLevelButton)
	{
		SelectLevelButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::LevelSelected);
		SelectLevelButton->OnHovered.AddDynamic(this, &USTULevelItemWidget::HoverLevel);
		SelectLevelButton->OnUnhovered.AddDynamic(this, &USTULevelItemWidget::UnhoverLevel);

	}
}

void USTULevelItemWidget::SetColorSelectedPicture(bool IsVisible)
{
	PictureLevel->SetColorAndOpacity(IsVisible ? FLinearColor::Red : FLinearColor::White);
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
