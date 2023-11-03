// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"
#include "Enums/CharacterEnums.h"

#include "BaseCharacter.generated.h"

UCLASS()
class BATTLE_API ABaseCharacter : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()
private:
	/********************
	* Attributes Properties
	********************/
	UPROPERTY(EditDefaultsOnly, category = "TOSET Data")
	FName ID;

	/********************
	* Data Properties
	********************/
	// Data table for search
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Data")
	class UDataTable* AttributeDataTable;

	// Max HP
	int32 HP = 100;

	// Stamina
	int32 Stamina = 100;

	/********************
	* Character Current Properties
	********************/
	// Current HP
	int32 CurrentHP = 100;

	// Current Stamina
	int32 CurrentStamina = 100;

	/********************
	* Character Current Equipments
	********************/
	// Current Weapon
	class ABaseWeapon* CurrentWeapon;

	/********************
	* Character Montage Properties
	********************/
	// Light Attack Montage
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Montage")
	UAnimMontage* LightAttackMontage;

	// Light Attack Montage Sections' names
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Montage")
	TArray<FName> LightAttackMontageSections;

	// Light Attack Montage Current Section's Index
	int32 LightAttackMontageIndex = 0;

	// Timer to refresh index to 0 in certain sections
	struct FTimerHandle LightAttackTimer;

	// Die Montage
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Montage")
	UAnimMontage* DieMontage;

	// Die Montage Sections' names
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Montage")
	TArray<FName> DieMontageSections;

	// Death life span
	UPROPERTY(EditAnywhere, Category = "TOSET Combat");
	float DeathLifeSpan = 5.f;

	// Hit result while sphere tracing, the pawn to focus
	class ABaseCharacter* FocusCharacter;

	// Character Action State
	ECharacterActionState CharacterActionState = ECharacterActionState::Unoccupied;

	// Anim instance
	UAnimInstance* AnimInstance;

	/********************
	* Character AI Properties
	********************/
	UPROPERTY(EditDefaultsOnly, Category = "TOSET AI")
	class UBehaviorTree* BehaviorTree;



public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Get Hit Interface
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	// Take damage when weapon apply damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Destroyed() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/********************
	* Initialize Functions
	********************/
	// Initialize Character properties
	void InitializeCharacterProperties();

	// Initialize Character states
	virtual void InitializeCharacterStates();

	// Initialize Character Attributes
	void InitializeAttributes(FName CharacterID);

	// Calculate the angle of hit and actor location
	double HitTheta(const FVector& ImpactPoint);

	// Die
	void CheckCharacterDie(const FVector& ImpactPoint);

	// Focus on enemy
	void FocusOnEnemy();

	// Stop focusing on enemy
	void StopFocusing();
private:
public:
	FORCEINLINE FName GetID() const { return ID; }
	FORCEINLINE int32 GetHP() const { return HP; }
	FORCEINLINE int32 GetStamina() const { return Stamina; }
	FORCEINLINE int32 GetCurrentHP() const { return CurrentHP; }
	FORCEINLINE int32 GetCurrentStamina() const { return CurrentStamina; }
	FORCEINLINE void SetCurrentHP(int32 InputHP) { CurrentHP = InputHP; }
	FORCEINLINE void SetCurrentStamina(int32 InputStamina) { CurrentStamina = InputStamina; }
	FORCEINLINE ABaseWeapon* GetCurrentWeapon() { return CurrentWeapon; }
	FORCEINLINE void SetCurrentWeapon(class ABaseWeapon* BaseWeapon) { CurrentWeapon = BaseWeapon; }
	FORCEINLINE UAnimMontage* GetLightAttackMontage() const { return LightAttackMontage; }
	FORCEINLINE TArray<FName> GetLightAttackMontageSections() const { return LightAttackMontageSections; }
	FORCEINLINE int32 GetLightAttackMontageIndex() const { return LightAttackMontageIndex; }
	FORCEINLINE FTimerHandle& GetLightAttackTimer() { return LightAttackTimer; }
	FORCEINLINE void SetLightAttackMontageIndex(int32 Index) { LightAttackMontageIndex = Index; }
	FORCEINLINE ABaseCharacter* GetFocusCharacter() const { return FocusCharacter; }
	FORCEINLINE void SetFocusCharacter(ABaseCharacter* Character) { FocusCharacter = Character; }
	FORCEINLINE void SetCharacterActionState(ECharacterActionState State) { CharacterActionState = State; }
	FORCEINLINE ECharacterActionState GetCharacterActionState() { return CharacterActionState; }
	FORCEINLINE UAnimInstance* GetAnimInstance() { return AnimInstance; }
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
};
