// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/AttackCollisionAnimNotifyState.h"
#include "Characters/BaseCharacter.h"
#include "Items/Weapons/BaseWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Macros/GeneralMacros.h"

void UAttackCollisionAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (BaseCharacter == nullptr) return;
	BaseCharacter->GetCurrentWeapon()->GetCapsuleComponent()->SetCollisionProfileName(ITEM_PROFILENAME);
}

void UAttackCollisionAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (BaseCharacter == nullptr) return;
	BaseCharacter->GetCurrentWeapon()->GetCapsuleComponent()->SetCollisionProfileName(WITHOUTCOLLISION_PROFILENAME);
}
