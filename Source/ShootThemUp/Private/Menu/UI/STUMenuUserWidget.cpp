// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/STUMenuUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	StarGameButton->OnClicked.AddDynamic(this, &USTUMenuUserWidget::StartGame);

}

void USTUMenuUserWidget::StartGame()
{
	UGameplayStatics::OpenLevel(this, FName("TestMap"));
}
