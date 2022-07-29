// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "STUSoundFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUSoundFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		static void SetVolumeSoundClass(class USoundClass* SoundClass, float Volume);

	UFUNCTION(BlueprintCallable)
		static void ToggleSoundClassVoume(USoundClass* SoundClass);
	
};
