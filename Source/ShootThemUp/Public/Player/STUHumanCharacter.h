// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUCharacter.h"
#include "STUHumanCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHumanCharacter : public ASTUCharacter
{
	GENERATED_BODY()

public:

	ASTUHumanCharacter(const FObjectInitializer& ObjInit);

private://variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CameraSphere;

	//UPROPERTY(BlueprintReadOnly, Category= "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsRun;

	//UPROPERTY(BlueprintReadOnly, Category= "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsMoveForward;

private://functions

	void MoveForward(float Value);
	void MoveRight(float Value);

	void Run();
	void StopRun();

	UFUNCTION()
	void OnCameraSphereBeginOverlap
	(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCameraSphereEndOverlap
	(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void UpdateVisibleMeshAndComponents();

protected://functnios

	virtual void DeathChar() override;

	virtual void BeginPlay() override;

public://functnios

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool IsRunning() const override;
};
