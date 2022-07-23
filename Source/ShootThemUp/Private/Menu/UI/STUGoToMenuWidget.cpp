// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/STUGoToMenuWidget.h"
#include "Components/Button.h"
#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGoToMenuWidget, All, All)

void USTUGoToMenuWidget::GoToMainMenu()
{
	if (!GetWorld()) return;
	const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if (!GameInstance) return;

	if (GameInstance->GetMainMenuName().IsNone())
	{
		UE_LOG(LogSTUGoToMenuWidget, Error, TEXT("MainMenuName None"));
		return;
	}

	UGameplayStatics::OpenLevel(this, GameInstance->GetMainMenuName());
}

void USTUGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::GoToMainMenu);
	}
}
