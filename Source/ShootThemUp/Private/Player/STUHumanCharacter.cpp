// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STUHumanCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "STUWeaponComponent.h"

// Sets default values
ASTUHumanCharacter::ASTUHumanCharacter
(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector((0.000000, 100.000000, 80.000000));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	bIsRun = (false);
	bIsMoveForward = (false);
}

// Called to bind functionality to input
void ASTUHumanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUHumanCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUHumanCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUHumanCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUHumanCharacter::StopRun);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);

	PlayerInputComponent->BindAction("ReloadWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);
}

void ASTUHumanCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
	bIsMoveForward = Value != 0;
}

void ASTUHumanCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASTUHumanCharacter::Run()
{
	bIsRun = true;
	/*if(bIsMoveForward)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintWalkSpeed;

	}*/
}

void ASTUHumanCharacter::StopRun()
{
	//GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	bIsRun = false;
}

bool ASTUHumanCharacter::IsRunning() const
{
	return bIsRun && bIsMoveForward && !GetVelocity().IsZero();
}

void ASTUHumanCharacter::DeathChar()
{
	Super::DeathChar();
	if (Controller) Controller->ChangeState(NAME_Spectating);
}
