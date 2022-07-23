#pragma once

#include "STUCoreTypes.generated.h"


//weapon
//STUWeaponComponent
USTRUCT(BlueprintType)
struct FWeaponType
{
	GENERATED_BODY()

		//Choose weapon
	UPROPERTY(EditDefaultsOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASTUBaseWeapon> WeaponClass;

	//Choose reload animation montage
	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* ReloadMontage;
};


//STUBaseWeapon
DECLARE_MULTICAST_DELEGATE_OneParam(FOnReloadSignature, ASTUBaseWeapon*)

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = "1"));
	int32 Bullet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (EditCondition = "!bHasInfinityAmmo", ClampMin = "0"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	bool bHasInfinityAmmo;
};

USTRUCT(BlueprintType)
struct FDataWeaponUI
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Icon");
	UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Icon");
	UTexture2D* CroshairIcon;

};

//Health
//STUHealthComponent

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChangeHealthSignature, float, float);


//FX
USTRUCT(BlueprintType)
struct FDecalData
{

	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Icon");
	class UMaterialInstance* Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Icon");
	FVector Size = FVector(10.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Icon");
	float LifeTime = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Icon");
	float FadeOutTime = 0.7f;
};

USTRUCT(BlueprintType)
struct FImpactData
{

	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Icon");
	 FDecalData Decal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Icon");
	class UNiagaraSystem* NiagaraEffect;
};

//GameMode
USTRUCT(BlueprintType)
struct FGameModeData
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "AI", meta = (ClampMin = "1"))
	int32 PlayersNum = 2;

	UPROPERTY(EditAnywhere, Category = "Rounds", meta = (ClampMin = "1"))
	int32 Rounds = 3;

	UPROPERTY(EditAnywhere, Category = "Rounds", meta = (ClampMin = "1"))
	int32 TimerComeDown = 3;//in second

	UPROPERTY(EditAnywhere, Category = "AI", meta = (ClampMin = "1"))
	int32 RespawnTime = 3;//in second

	UPROPERTY(EditAnywhere, Category = "Color")
	FLinearColor DefaultColor = FLinearColor::Black;

	UPROPERTY(EditAnywhere, Category = "Color")
	TArray<FLinearColor> TeamsColor;
};

UENUM(BlueprintType)
enum class EGameState : uint8
{
	EGS_WaintingToStart UMETA(DisplayName =  "Wainting To Start"),
	EGS_InProgress UMETA(DisplayName = "In Progress"),
	EGS_GameOver UMETA(DisplayName = "GameOver"),
	EGS_Paused UMETA(DisplayName = "Paused"),

	EGS_Max UMETA(DisplayName = "Default")
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, EGameState);


//STULevelItemWidget
USTRUCT(BlueprintType)
struct FLevelData
{

	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, Category = "LevelWidget")
	FName DisplayName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "LevelWidget")
	FName LevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "LevelWidget")
	class UTexture2D* LevelPicture;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelected,const FLevelData &)