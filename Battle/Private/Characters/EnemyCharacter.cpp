// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"
#include "UI/Enemy/HealthWidgetComponent.h"
#include "Items/Weapons/BaseWeapon.h"
#include "UI/Enemy/EnemyHealthBarWidget.h"
#include "Components/CapsuleComponent.h"
#include "Macros/GeneralMacros.h"
#include "AI/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AnimInstance/LocomotionAnimInstance.h"


AEnemyCharacter::AEnemyCharacter()
{
	GetCapsuleComponent()->SetCollisionProfileName(ENEMY_PROFILENAME);
	InitializeUI();
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	LocomotionAnimInstance = Cast<ULocomotionAnimInstance>(GetMesh()->GetAnimInstance());


	if (EnemyWeaponClass == nullptr) return;
	ABaseWeapon* EnemyWeapon = GetWorld()->SpawnActor<ABaseWeapon>(EnemyWeaponClass);
	EnemyWeapon->EquipWeapon(this);
	BaseAIController = Cast<ABaseAIController>(GetController());
	HideHealthBar();


}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Distance = GetDistanceTo(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (BaseAIController)
	{
		bool IsInCombat = BaseAIController->GetBlackboardComponent()->GetValueAsBool(FName("IsInCombat"));
		if (IsInCombat == false)
			HideHealthBar();
		else if (Distance >= InterestRadius)
			BaseAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsInCombat"), false);
		if (Distance <= MeleeAttackRange)
		{
			BaseAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsInAttackRange"), true);
		}
			else
		{
			BaseAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsInAttackRange"), false);
		}
	}

	
}

void AEnemyCharacter::GetHit_Implementation(const FVector& ImpactPoint)
{
	Super::GetHit_Implementation(ImpactPoint);
	ShowHealthBar();
	if (GetCurrentHP() <= 0) HideHealthBar();

	if (BaseAIController) BaseAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsInCombat"), true);
}

void AEnemyCharacter::Destroyed()
{
	Super::Destroyed();
	if (BaseAIController) BaseAIController->Destroy();
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

void AEnemyCharacter::Attack()
{
	if (LocomotionAnimInstance == nullptr) return;
	if (GetLightAttackMontage() == nullptr) return;
	//if (GetLightAttackMontageSections().Num() <= 0) return;
	LocomotionAnimInstance->Montage_Play(GetLightAttackMontage(), 1.4f);
}
