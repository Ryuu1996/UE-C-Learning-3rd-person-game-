// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "BaseCharacter.generated.h"

UCLASS()
class BATTLE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
private:
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
public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
	void InitializeAttributes(FName ID);

private:
public:
	FORCEINLINE int32 GetHP() const { return HP; }
	FORCEINLINE int32 GetStamina() const { return Stamina; }
	FORCEINLINE int32 GetCurrentHP() const { return CurrentHP; }
	FORCEINLINE int32 GetCurrentStamina() const { return CurrentStamina; }
	FORCEINLINE void SetCurrentHP(int32 InputHP) { CurrentHP = InputHP; }
	FORCEINLINE void SetCurrentStamina(int32 InputStamina) { CurrentStamina = InputStamina; }
	FORCEINLINE ABaseWeapon* GetCurrentWeapon() { return CurrentWeapon; }
	FORCEINLINE void SetCurrentWeapon(class ABaseWeapon* BaseWeapon) { CurrentWeapon = BaseWeapon; }
};
