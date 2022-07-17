// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUPauseWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

bool USTUPauseWidget::Initialize()
{
    const bool bInitStatus = Super::Initialize();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::ContinueGame);
    }

    return bInitStatus;
}

void USTUPauseWidget::ContinueGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
