// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/AttackCollisionAnimNotifyState.h"
#include "Characters/PlayerCharacter.h"
#include "Items/Weapons/BaseWeapon.h"
#include "Components/CapsuleComponent.h"

void UAttackCollisionAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (PlayerCharacter == nullptr) return;
	PlayerCharacter->GetCurrentWeapon()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UAttackCollisionAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (PlayerCharacter == nullptr) return;
	PlayerCharacter->GetCurrentWeapon()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
