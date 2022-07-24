// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUAICharacter.h"
#include "Components/STUAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BrainComponent.h"
#include "AI/STUAIController.h"
#include "UI/STUHealthBarWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/WidgetComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjInit):
Super(ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;

	bUseControllerRotationYaw = false;
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}

	HealthWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("healthWidget"));
	HealthWidget->SetupAttachment(GetRootComponent());
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidget->SetDrawAtDesiredSize(true);

	DistanceDrawHealhtWidget = 1000.f;
}

void ASTUAICharacter::UpdateHealthWidgetVisibility()
{
	if (!GetWorld() || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()) return;
	
	const FVector MainPawnLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	const float DistanceBetweenPawns= FVector::Distance(GetActorLocation(), MainPawnLocation);

	HealthWidget->SetVisibility(DistanceBetweenPawns < DistanceDrawHealhtWidget);
}

void ASTUAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthWidget);
}

void ASTUAICharacter::Tick(float DeltaTime)
{
	UpdateHealthWidgetVisibility();
}

void ASTUAICharacter::OnChangeHealth(float Health, float DeltaHealth)
{
	Super::OnChangeHealth(Health, DeltaHealth);

	const auto UserWidget = Cast<USTUHealthBarWidget>(HealthWidget->GetUserWidgetObject());

	if (!UserWidget) return;

	UserWidget->SetHealth(HealthComponent->GetHealthPercentage());
}

void ASTUAICharacter::DeathChar()
{
	Super::DeathChar();

	ASTUAIController* AIController = Cast <ASTUAIController>(Controller);
	if (AIController && AIController->GetBrainComponent())
	{
		AIController->GetBrainComponent()->Cleanup();
	}
}

