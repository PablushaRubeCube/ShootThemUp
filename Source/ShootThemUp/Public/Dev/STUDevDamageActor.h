// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUDevDamageActor();

private://variables

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "SceneComponent", meta=(AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	//Radius debag sphere and damage sphere
 	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Damage", meta=(AllowPrivateAccess = "true"))
	float Radius;

	//Color Debug Sphere
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Debug", meta=(AllowPrivateAccess = "true"))
	FColor SphereColor;

	//is full damage to all sphere?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Damage", meta=(AllowPrivateAccess = "true"))
	bool bDoFullDamage;

	// Damage sphere value
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Damage", meta=(AllowPrivateAccess = "true"))
	float Damage;

	// Choose Damage Type for object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> DamageType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
