// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Data/AttributeRowBase.h"
#include "Macros/GeneralMacros.h"
#include "Items/Weapons/BaseWeapon.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AI/BaseAIController.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	InitializeCharacterProperties();
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::GetHit_Implementation(const FVector& ImpactPoint)
{
	CheckCharacterDie(ImpactPoint);
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHP = FMath::Clamp(CurrentHP - DamageAmount, 0.f, HP);
	return CurrentHP;
}

void ABaseCharacter::Destroyed()
{
	if (CurrentWeapon) CurrentWeapon->Destroy();
}

void ABaseCharacter::InitializeCharacterProperties()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetMesh()->AddLocalRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionProfileName(WITHOUTCOLLISION_PROFILENAME);
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.f, 800.f, 0.f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->AirControl = 1.f;
	GetCharacterMovement()->MaxWalkSpeed = 700.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void ABaseCharacter::InitializeCharacterStates()
{

}

void ABaseCharacter::InitializeAttributes(FName CharacterID)
{
	FAttributeRowBase* AttributeRowBase = AttributeDataTable->FindRow<FAttributeRowBase>(CharacterID, FString(""));
	HP = AttributeRowBase->HP;
	Stamina = AttributeRowBase->Stamina;
	CurrentHP = HP;
	CurrentStamina = Stamina;
}

double ABaseCharacter::HitTheta(const FVector& ImpactPoint)
{
	const FVector Forward = GetActorForwardVector();
	const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	const FVector ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();
	const double CosTheta = FVector::DotProduct(Forward, ToHit);
	double Theta = FMath::Acos(CosTheta);
	Theta = FMath::RadiansToDegrees(Theta);//if CrossProduct points down, Theta should be negative
	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);
	if (CrossProduct.Z < 0)
	{
		Theta *= -1.f;
	}
	return Theta;
}

void ABaseCharacter::CheckCharacterDie(const FVector& ImpactPoint)
{
	if (GetCurrentHP() > 0) return;
	double Theta = HitTheta(ImpactPoint);
	FName Section;
	if (Theta >= -135.f && Theta <= 135.f)
		// Fall Back
		Section = DieMontageSections[0];
	else
		// Fall Forward
		Section = DieMontageSections[1];

	// Play die montage
	if (AnimInstance == nullptr) return;
	if (DieMontage == nullptr) return;
	AnimInstance->StopAllMontages(0.1);
	AnimInstance->Montage_Play(DieMontage, 0.7f);
	AnimInstance->Montage_JumpToSection(Section, DieMontage);
	SetCharacterActionState(ECharacterActionState::Occupied);

	// After play die montage
	GetCharacterMovement()->bOrientRotationToMovement = false;
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(GetController());
	if (BaseAIController)
	{
		BaseAIController->GetBrainComponent()->StopLogic(FString("Character Dies"));
		SetLifeSpan(DeathLifeSpan);
	}
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

}

void ABaseCharacter::FocusOnEnemy()
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FocusCharacter->GetActorLocation());
	// To make camera more comfortable to see
	LookAtRotation.Pitch = -30;
	GetController()->SetControlRotation(LookAtRotation);
	// To avoid to set actor's pitch rotation
	LookAtRotation.Pitch = 0;
	SetActorRotation(LookAtRotation);
}

void ABaseCharacter::StopFocusing()
{
	FocusCharacter = nullptr;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeAttributes(GetID());
	AnimInstance = GetMesh()->GetAnimInstance();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


