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
	* Attributes Properties
	********************/
	UPROPERTY(EditDefaultsOnly, category = "TOSET Data")
	FName ID;

	/********************
	* UI Properties
	********************/
	// Health Widget Component
	UPROPERTY(VisibleDefaultsOnly)
	class UHealthWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "TOSET UI")
	TSubclassOf<UUserWidget> EnemyHealthBarWidgetClass;

	/********************
	* Mesh Properties
	********************/
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Weapon")
	TSubclassOf<class ABaseWeapon> EnemyWeaponClass;

public:
	AEnemyCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	void InitializeUI();

};
