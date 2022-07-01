// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASTUBaseWeapon();


private://functions



protected://variables

	//skeletal mesh our weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float MaxShotDistance;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName SocketName = "MuzzleFlashSocket";



protected://functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	//functions
	virtual	void StartFireWeapon();
	virtual	void StopFireWeapon();
	virtual void MakeShot();

	APlayerController* GetPlayerController() const;
	bool GetViewPort(FVector& ViewLocation, FRotator& ViewRotator) const;
	FVector GetMuzzleLocation() const;
	virtual bool GetTraceData(FVector& StartTrace, FVector& EndTrace)  const;
	void MakeHit(const UWorld* World, FHitResult& HitResult, const FVector& StartTrace, const FVector& EndTrace) const;

	

};