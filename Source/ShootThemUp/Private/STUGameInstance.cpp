// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameInstance.h"
#include "Sounds/STUSoundFunctionLibrary.h"

void USTUGameInstance::ToggleSoundClassVolume()
{
	USTUSoundFunctionLibrary::ToggleSoundClassVoume(MasterVolumeClass);
}
