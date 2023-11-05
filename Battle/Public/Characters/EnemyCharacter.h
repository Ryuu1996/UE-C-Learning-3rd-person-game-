// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
private:
	/********************
	* General Properties
	********************/
	// Controller
	class ABaseAIController* BaseAIController;

	// Locomotion Anim Instance
	class ULocomotionAnimInstance* LocomotionAnimInstance;

	/********************
	* UI Properties
	********************/
	// Health Widget Component
	UPROPERTY(VisibleDefaultsOnly)
	class UHealthWidgetComponent* HealthWidgetComponent;

	// The class of Blueprint health bar
	UPROPERTY(EditDefaultsOnly, Category = "TOSET UI")
	TSubclassOf<UUserWidget> EnemyHealthBarWidgetClass;

	/********************
	* Mesh Properties
	********************/
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Weapon")
	TSubclassOf<class ABaseWeapon> EnemyWeaponClass;

	/********************
	* Combat Properties
	********************/
	// When player out of range, Enemy lose interest
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Combat")
	double InterestRadius = 2000.f;

	// Melee Attack Range
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Combat")
	float MeleeAttackRange = 130.f;
public:
	// Constructor
	AEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Get Hit Interface
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	// On character destoryed
	virtual void Destroyed() override;

	// Attack
	void Attack();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	// Initialize UI
	void InitializeUI();

	// Show health bar
	void ShowHealthBar();

	// Hide health bar
	void HideHealthBar();

};
