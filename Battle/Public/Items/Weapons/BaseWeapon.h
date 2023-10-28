// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"

#include "BaseWeapon.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API ABaseWeapon : public ABaseItem
{
	GENERATED_BODY()
private:	
	/********************
	* Data Properties
	********************/
	// Data table for search
	UPROPERTY(EditDefaultsOnly, Category = "TOSET Data")
	class UDataTable* WeaponDataTable;

	int32 Damage = 0;
public:
	// Equip weapon
	virtual void EquipWeapon(class ABaseCharacter* Character);
protected:
	void InitializeData(FName RowName);
private:
public:
	FORCEINLINE int32 GetDamage() const { return Damage; }

};
