// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"
#include "UI/Enemy/HealthWidgetComponent.h"
#include "Items/Weapons/BaseWeapon.h"
#include "UI/Enemy/EnemyHealthBarWidget.h"
#include "Components/CapsuleComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetCapsuleComponent()->SetCollisionProfileName("Enemy");
	InitializeUI();

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (EnemyWeaponClass == nullptr) return;
	ABaseWeapon* EnemyWeapon = GetWorld()->SpawnActor<ABaseWeapon>(EnemyWeaponClass);
	EnemyWeapon->EquipWeapon(this);
	InitializeAttributes(ID);
	HealthWidgetComponent->SetProgressBarHealth(GetCurrentHP() / GetHP());
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
}

void AEnemyCharacter::HideHealthBar()
{
	if (HealthWidgetComponent == nullptr) return;
	HealthWidgetComponent->SetVisibility(false);
}
