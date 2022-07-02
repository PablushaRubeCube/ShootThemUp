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
#include "Components/CapsuleComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogCharacter,All,All)

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
	SpringArmComponent->TargetOffset = FVector(( 0.000000, 100.000000, 80.000000));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>(TEXT("HealthComponent"));

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>(TEXT("WeaponComponent"));

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthTextComponent"));
	HealthTextComponent->SetupAttachment(RootComponent);
	HealthTextComponent->bOwnerNoSee = true;
	
	bIsRun = (false);
	bIsMoveForward = (false);

	LandedDamage = FVector2D(10.f, 100.f);
	LandedDamageVelocity = FVector2D(700.f, 1200.f);

	LifeSpanOnDeath = 5.f;
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

	SetLifeSpan(LifeSpanOnDeath);

	if (Controller) Controller->ChangeState(NAME_Spectating);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	WeaponComponent->StopFire();
}

void ASTUCharacter::OnChangeHealth(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASTUCharacter::OnGroudLanded(const FHitResult& Hit)
{
	const float ZVelocity = -GetCharacterMovement()->Velocity.Z;
	if (ZVelocity < LandedDamageVelocity.X) return;

	const float FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, ZVelocity);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
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
	LandedDelegate.AddDynamic(this, &ASTUAICharacter::OnGroudLanded);


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

	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ACharacter::Jump);
	
	PlayerInputComponent->BindAction("Run",IE_Pressed, this, &ASTUCharacter::Run);
	PlayerInputComponent->BindAction("Run",IE_Released, this, &ASTUCharacter::StopRun);

	PlayerInputComponent->BindAction("Fire",IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire",IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);
}


