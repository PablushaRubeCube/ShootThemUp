// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUWeaponComponent.h"

#include "Player/STUCharacter.h"
#include "Weapon/STUBaseWeapon.h"
#include "Animations/STUEquipWeaponAnimNotify.h"
#include "Animations/STUReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LOGSTUWeaponComponent, All, All)

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent():
SocketWeaponEquipName("WeaponEquipPoint"),
SocketWeaponArmoryName("WeaponArmoryPoint"),
bEquipInProgress(false),
bReloadInProgress(false),
CurrentWeapon(nullptr),
IndexWeapon(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapons();
	InitialAnimation();
	EquipWeapon(IndexWeapon);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::SpawnWeapons()
{
	UWorld* World = GetWorld();
	ASTUCharacter* Char = Cast<ASTUCharacter>(GetOwner());
	if (World && Char)
	{
		for(auto WeaponTypeInst : WeaponType)
		{
		 ASTUBaseWeapon* SpawndedWeapon = World->SpawnActor<ASTUBaseWeapon>(WeaponTypeInst.WeaponClass);
			if(SpawndedWeapon)
			{
				SpawndedWeapon->SetOwner(GetOwner());
				Weapons.Add(SpawndedWeapon);
				AttachWeaponToSocket(SpawndedWeapon, Char->GetMesh(), SocketWeaponArmoryName);
				SpawndedWeapon->OnReloadSignature.AddUObject(this, &USTUWeaponComponent::ClipIsEmpty);
			}
		}
	}
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon,USceneComponent* SceneComponent,const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentTransformRules, SocketName);
}

void USTUWeaponComponent::EquipWeapon(int32 Index)
{
	if (Index < 0 || Index >= Weapons.Num())
	{
		UE_LOG(LOGSTUWeaponComponent, Warning, TEXT("Invalid Index EquipWeapon"))
		return;
	}

	ASTUCharacter* Char = Cast<ASTUCharacter>(GetOwner());
	if (!Char) return;
	
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFireWeapon();
		AttachWeaponToSocket(CurrentWeapon, Char->GetMesh(), SocketWeaponArmoryName);
	}
	CurrentWeapon = Weapons[Index];

	const auto WeaponData =
	WeaponType.FindByPredicate([&](const FWeaponType& Data)
	{ return Data.WeaponClass == CurrentWeapon->GetClass(); });
	CurrentReloadMontage = WeaponData ? WeaponData->ReloadMontage : nullptr;

	if (CurrentWeapon)
	{
		AttachWeaponToSocket(CurrentWeapon, Char->GetMesh(), SocketWeaponEquipName);
	}
	WeaponMontageAnimation(EquipMontage);
	bEquipInProgress = true;

}

void USTUWeaponComponent::WeaponMontageAnimation(UAnimMontage* Montage)
{
	ASTUCharacter* Char = Cast<ASTUCharacter>(GetOwner());
	if (!Char) return;

	Char->PlayAnimMontage(Montage);
}

void USTUWeaponComponent::InitialAnimation()
{
		auto CurrentEquipNotify = AnimUtils::FindNotifyByClass<USTUEquipWeaponAnimNotify>(EquipMontage);
		if (CurrentEquipNotify)
		{
			CurrentEquipNotify->OnNotifyCall.AddUObject(this, &USTUWeaponComponent::OnFinishEquip);
		}
		else
		{
			UE_LOG(LOGSTUWeaponComponent, Warning, TEXT("Notify don't find"));
		}

		for (auto CurrentWeaponType : WeaponType) 
		{
			auto CurrentReloadNotify = AnimUtils::FindNotifyByClass<USTUReloadFinishedAnimNotify>(CurrentWeaponType.ReloadMontage);
			if (!CurrentReloadNotify)
			{
				UE_LOG(LOGSTUWeaponComponent, Warning, TEXT("Notify don't find"));
			}
			CurrentReloadNotify->OnNotifyCall.AddUObject(this, &USTUWeaponComponent::OnFinishReload);
		}
		
}

void USTUWeaponComponent::OnFinishEquip(USkeletalMeshComponent* SkeletalMesh)
{
	ASTUCharacter* Char = Cast<ASTUCharacter>(GetOwner());
	if (!Char || (Char->GetMesh() != SkeletalMesh)) return;
	
	bEquipInProgress = false;
}

void USTUWeaponComponent::OnFinishReload(USkeletalMeshComponent* SkeletalMesh)
{
	ASTUCharacter* Char = Cast<ASTUCharacter>(GetOwner());
	if (!Char || (Char->GetMesh() != SkeletalMesh)) return;

	bReloadInProgress = false;
}

void USTUWeaponComponent::StartFire()
{
	if(IsCanFire())
	{
		CurrentWeapon->StartFireWeapon();
	}
}

void USTUWeaponComponent::StopFire()
{
	if(CurrentWeapon)
	{
		CurrentWeapon->StopFireWeapon();
	}
}

void USTUWeaponComponent::NextWeapon()
{
	if (IsEquipInProgress() ||IsReloadInProgress()) return;
	IndexWeapon = (IndexWeapon + 1) % Weapons.Num();
	EquipWeapon(IndexWeapon);
}

bool USTUWeaponComponent::IsCanFire() const
{
	return (CurrentWeapon && !IsEquipInProgress() && !IsReloadInProgress());
}

bool USTUWeaponComponent::IsCanReload() const
{
	return (CurrentWeapon && !IsEquipInProgress() && !IsReloadInProgress() && CurrentWeapon->IsWeaponCanReload());
}

void USTUWeaponComponent::Reload() 
{
	ChangeClip();
}

bool USTUWeaponComponent::GetCurrentDataWeaponUI(FDataWeaponUI& Data) const
{
	if (!CurrentWeapon) return false;

	Data = CurrentWeapon->GetDataWeaponUI();
	return true;
}

bool USTUWeaponComponent::GetCurrentDataAmmo(FAmmoWeapon& Data) const
{
	if (!CurrentWeapon) return false;

	Data = CurrentWeapon->GetDataWeaponAmmo();
	return true;
}

bool USTUWeaponComponent::TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> Weapon, int32 Clips)
{
	for (auto WeaponInst : Weapons)
	{
		if (WeaponInst && WeaponInst->IsA(Weapon))
		{
			return	WeaponInst->TryToAddAmmo(Clips);
		}
	}
	return false;
}

bool USTUWeaponComponent::NeedAmmo(TSubclassOf<ASTUBaseWeapon> Weapon)
{
	for (auto WeaponInst : Weapons)
	{
		if (WeaponInst && WeaponInst->IsA(Weapon))
		{
			return	!WeaponInst->IsAmmoFull();
		}
	}
	return false;
}

void USTUWeaponComponent::ClipIsEmpty(ASTUBaseWeapon* AmmoEmptyWeapon)
{
	if (!AmmoEmptyWeapon) return;
	if (CurrentWeapon == AmmoEmptyWeapon)
	{
		ChangeClip();
	}
	else
	{
		for (const auto Weapon : Weapons)
		{
			if (Weapon == AmmoEmptyWeapon)
			{
				Weapon->ReloadClip();
			}
		}
	}
	
}

void USTUWeaponComponent::ChangeClip()
{
	if (!IsCanReload())return;
	bReloadInProgress = true;
	CurrentWeapon->ReloadClip();
	CurrentWeapon->StopFireWeapon();
	WeaponMontageAnimation(CurrentReloadMontage);
	
}
