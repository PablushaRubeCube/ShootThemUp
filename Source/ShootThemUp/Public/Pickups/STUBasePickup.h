// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBasePickup();

private://variables

	//TimerHandel for respawn pickup
	FTimerHandle TimerHandle;

private://functions

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void PickupWasTaken();

	void RespawnPickup();

	float YawRotation;

protected://variables

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Mesh")
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	float TimerRespawnPickup;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundCue* PickupSound;

protected://functions

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool CanGivePickup(APawn* Pawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GenerateRotationYaw();

	bool IsCanPickup() const;

};
