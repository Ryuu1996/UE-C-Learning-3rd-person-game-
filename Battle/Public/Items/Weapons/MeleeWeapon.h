// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/BaseWeapon.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API AMeleeWeapon : public ABaseWeapon
{
	GENERATED_BODY()
private:
	// Player Character
	class APlayerCharacter* PlayerCharacter;
public:
	// Use Item
	virtual void UseItem_Implementation() override;
	// Equip Weapon
	virtual void EquipWeapon(class ABaseCharacter* Character) override;
protected:
private:
};
