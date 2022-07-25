// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/STUMenuUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Menu/UI/STULevelItemWidget.h"
#include "Components/HorizontalBox.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUMenuUserWidget, All, All)

void USTUMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StarGameButton)
	{
		StarGameButton->OnClicked.AddDynamic(this, &USTUMenuUserWidget::StartGame);
	}
	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuUserWidget::QuitGame);
	}
	InitialLevels();
}

void USTUMenuUserWidget::StartGame()
{
	PlayAnimation(HideAnimation);
}

void USTUMenuUserWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTUMenuUserWidget::InitialLevels()
{
	if (!GetWorld()) return;
	const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if (!GameInstance) return;

	checkf(GameInstance->GetLevels().Num() != 0, TEXT("Array Levels cant = 0"));

	if (!LevelBox) return;
	LevelBox->ClearChildren();

	for (auto LevelInstData : GameInstance->GetLevels())
	{
		const auto CreatedWidget = CreateWidget<USTULevelItemWidget>(GetWorld(), ToSpawnLevelWidget);
		if (!CreatedWidget) continue;
		
		CreatedWidget->SetWidgetLevelData(LevelInstData);
		CreatedWidget->OnLevelSelected.AddUObject(this, &USTUMenuUserWidget::Selectlevel);
		LevelWidets.Add(CreatedWidget);
		
		LevelBox->AddChild(CreatedWidget);
	}
	if (GameInstance->GetSelectedLevel().LevelName.IsNone())
	{
		Selectlevel(GameInstance->GetLevels()[0]);
	}
	else
	{
		Selectlevel(GameInstance->GetSelectedLevel());
	}
}

void USTUMenuUserWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation != HideAnimation) return;
	if (!GetWorld()) return;
	const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if (!GameInstance) return;

	UGameplayStatics::OpenLevel(this, GameInstance->GetSelectedLevel().LevelName);
}


void USTUMenuUserWidget::Selectlevel(const FLevelData& Data)
{
	if (!GetWorld()) return;
	const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if (!GameInstance) return;

	GameInstance->SetSelectedLevel(Data);

	for (auto WidgetInst : LevelWidets)
	{
		if (!WidgetInst) continue;

		bool IsCurrentLevelName = WidgetInst->GetWidgetLevelData().LevelName == Data.LevelName;

		WidgetInst->SetColorSelectedPicture(IsCurrentLevelName);
	}
}
