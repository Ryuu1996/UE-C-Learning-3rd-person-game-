// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/MeleeWeapon.h"
#include "Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Enums/CharacterEnums.h"



void AMeleeWeapon::UseItem_Implementation()
{
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter == nullptr) return;
	PlayerCharacter->SetCharacterEquipState(ECharacterEquipState::AxeEquipped);
	EquipWeapon();
}

void AMeleeWeapon::EquipWeapon()
{
	SetOwner(PlayerCharacter);
	SetInstigator(PlayerCharacter);
	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	GetStaticMeshComponent()->AttachToComponent(PlayerCharacter->GetMesh(), AttachmentTransformRules, FName("RightHandSocket"));
}
