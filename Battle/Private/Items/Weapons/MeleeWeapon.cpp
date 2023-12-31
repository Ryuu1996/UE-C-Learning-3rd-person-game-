// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/MeleeWeapon.h"
#include "Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Enums/CharacterEnums.h"
#include "Components/CapsuleComponent.h"



void AMeleeWeapon::UseItem_Implementation()
{
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter == nullptr) return;
	PlayerCharacter->SetCharacterEquipState(ECharacterEquipState::AxeEquipped);
	EquipWeapon(PlayerCharacter);
}

void AMeleeWeapon::EquipWeapon(ABaseCharacter* Character)
{
	Super::EquipWeapon(Character);
}

