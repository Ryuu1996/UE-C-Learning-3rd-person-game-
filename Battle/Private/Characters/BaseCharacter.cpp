// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Data/AttributeRowBase.h"

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

void ABaseCharacter::InitializeCharacterProperties()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetMesh()->AddLocalRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionProfileName("WithoutCollision");
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

void ABaseCharacter::InitializeAttributes(FName ItemID)
{
	FAttributeRowBase* AttributeRowBase = AttributeDataTable->FindRow<FAttributeRowBase>(ItemID, FString(""));
	HP = AttributeRowBase->HP;
	Stamina = AttributeRowBase->Stamina;
	CurrentHP = HP;
	CurrentStamina = Stamina;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


