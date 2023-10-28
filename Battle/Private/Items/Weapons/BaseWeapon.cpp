// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/BaseWeapon.h"
#include "Characters/BaseCharacter.h"
#include "Data/WeaponRowBase.h"


void ABaseWeapon::EquipWeapon(ABaseCharacter* Character)
{
	SetItemEquipState(EItemEquipState::Equipped);
}

void ABaseWeapon::InitializeData(FName ItemID)
{
	FWeaponRowBase* WeaponRowBase = WeaponDataTable->FindRow<FWeaponRowBase>(ItemID, FString(""));
	Damage = WeaponRowBase->Damage;
}
