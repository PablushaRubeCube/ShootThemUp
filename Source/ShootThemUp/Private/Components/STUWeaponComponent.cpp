// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUWeaponComponent.h"

#include "Player/STUCharacter.h"
#include "Weapon/STUBaseWeapon.h"
#include "Animations/STUEquipWeaponAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(STUWeaponComponent, All, All)

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent():
SocketWeaponEquipName("WeaponEquipPoint"),
SocketWeaponArmoryName("WeaponArmoryPoint"),
IndexWeapon(0),
CurrentWeapon(nullptr),
bEquipInProgress(false)
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
		UE_LOG(STUWeaponComponent, Warning, TEXT("Invalid Index"))
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
	const auto Notifies = EquipMontage->Notifies;
	for (auto NotifyInst : Notifies)
	{
		USTUEquipWeaponAnimNotify* CurrentNotify = Cast<USTUEquipWeaponAnimNotify>(NotifyInst.Notify);
		if (CurrentNotify)
		{
			CurrentNotify->OnNotifyCall.AddUObject(this, &USTUWeaponComponent::OnFinishEquip);
			break;
		}
	}
}

void USTUWeaponComponent::OnFinishEquip(USkeletalMeshComponent* SkeletalMesh)
{
	ASTUCharacter* Char = Cast<ASTUCharacter>(GetOwner());
	if (!Char || (Char->GetMesh() != SkeletalMesh)) return;
	
	bEquipInProgress = false;
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
	if (IsEquipInProgress()) return;
	IndexWeapon = (IndexWeapon + 1) % Weapons.Num();
	EquipWeapon(IndexWeapon);
}

bool USTUWeaponComponent::IsCanFire() const
{
	return (CurrentWeapon && !IsEquipInProgress());
}

void USTUWeaponComponent::Reload() 
{
	WeaponMontageAnimation(CurrentReloadMontage);
}
