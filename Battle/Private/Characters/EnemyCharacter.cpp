// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"
#include "UI/Enemy/HealthWidgetComponent.h"
#include "Items/Weapons/BaseWeapon.h"
#include "UI/Enemy/EnemyHealthBarWidget.h"
#include "Components/CapsuleComponent.h"
#include "Macros/GeneralMacros.h"

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// TODO: healthbar range
}

void AEnemyCharacter::GetHit_Implementation(const FVector& ImpactPoint)
{
	Super::GetHit_Implementation(ImpactPoint);
	ShowHealthBar();
	if (GetCurrentHP() <= 0) HideHealthBar();
}


AEnemyCharacter::AEnemyCharacter()
{
	GetCapsuleComponent()->SetCollisionProfileName(ENEMY_PROFILENAME);
	InitializeUI();

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (EnemyWeaponClass == nullptr) return;
	ABaseWeapon* EnemyWeapon = GetWorld()->SpawnActor<ABaseWeapon>(EnemyWeaponClass);
	EnemyWeapon->EquipWeapon(this);
	HideHealthBar();
}

void AEnemyCharacter::InitializeUI()
{
	HealthWidgetComponent = CreateDefaultSubobject<UHealthWidgetComponent>(TEXT("HealthWidgetComponent"));
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->AddLocalOffset(FVector(0.f, 0.f, 150.f));
	HealthWidgetComponent->SetWidgetClass(EnemyHealthBarWidgetClass);
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void AEnemyCharacter::ShowHealthBar()
{
	if (HealthWidgetComponent == nullptr) return;
	HealthWidgetComponent->SetVisibility(true);
	HealthWidgetComponent->SetProgressBarHealth(float(GetCurrentHP()) / float(GetHP()));
}

void AEnemyCharacter::HideHealthBar()
{
	if (HealthWidgetComponent == nullptr) return;
	HealthWidgetComponent->SetVisibility(false);
}
