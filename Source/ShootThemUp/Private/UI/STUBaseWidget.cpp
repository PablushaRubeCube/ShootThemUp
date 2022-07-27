// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUBaseWidget.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void USTUBaseWidget::PlayShowAnimation()
{
	PlayAnimation(ShowAnimation);
	UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
}
