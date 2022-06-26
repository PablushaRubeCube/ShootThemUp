// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STUCharacter.h"
#include "STUHealthComponent.h"
#include "STUWeaponComponent.h"
#include "AI/STUAICharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
ASTUCharacter::ASTUCharacter()
/*(const FObjectInitializer& ObjInit):
Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName)) */
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>(TEXT("HealthComponent"));

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>(TEXT("WeaponComponent"));

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthTextComponent"));
	HealthTextComponent->SetupAttachment(RootComponent);
	
	bIsRun = (false);
	bIsMoveForward = (false);
}

void ASTUCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
	bIsMoveForward = Value !=0;
}

void ASTUCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(),Value);
}

void ASTUCharacter::Run()
{
	bIsRun = true;	
	/*if(bIsMoveForward)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintWalkSpeed;
	
	}*/
}

void ASTUCharacter::StopRun()
{
	//GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	bIsRun = false;
}

float ASTUCharacter::GetMovementDirection() const
{
		if (GetVelocity().IsZero()) return 0.0f;
		const auto VelocityNormal = GetVelocity().GetSafeNormal();
		const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
		const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
		const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
		return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTUCharacter::DeathChar()
{
	PlayAnimMontage(DeathMontage);
	
	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.f);

	if (Controller) Controller->ChangeState(NAME_Spectating);
}

void ASTUCharacter::OnChangeHealth(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

bool ASTUCharacter::IsRunning() const
{
	return bIsRun && bIsMoveForward && !GetVelocity().IsZero();
}

// Called when the game starts or when spawned
void ASTUCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());

	OnChangeHealth(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this,&ASTUCharacter::DeathChar);
	HealthComponent->OnChangeHealth.AddUObject(this, &ASTUCharacter::OnChangeHealth);
}


// Called every frame
void ASTUCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// Called to bind functionality to input
void ASTUCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ACharacter::Jump);
	
	PlayerInputComponent->BindAction("Run",IE_Pressed, this, &ASTUCharacter::Run);
	PlayerInputComponent->BindAction("Run",IE_Released, this, &ASTUCharacter::StopRun);

	PlayerInputComponent->BindAction("Fire",IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire",IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
}