// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUProjectile();

private://variables

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectileComponent", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileComponent;

	//Prjetctile Direction
	FVector DirectionProjectile;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	FORCEINLINE void SetDirectionProjectile(FVector Direction) { DirectionProjectile = Direction; }

};
