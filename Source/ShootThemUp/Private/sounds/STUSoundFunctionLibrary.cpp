// Fill out your copyright notice in the Description page of Project Settings.


#include "sounds/STUSoundFunctionLibrary.h"
#include "Sound/SoundClass.h"

void USTUSoundFunctionLibrary::SetVolumeSoundClass(class USoundClass* SoundClass, float Volume)
{
	if (!SoundClass) return;
	SoundClass->Properties.Volume = Volume;
}

void USTUSoundFunctionLibrary::ToggleSoundClassVoume(USoundClass* SoundClass)
{
	if (!SoundClass) return;
	const float Volume = SoundClass->Properties.Volume > 0.f ? 0.f : 1.f ;
	SetVolumeSoundClass(SoundClass, Volume);
}