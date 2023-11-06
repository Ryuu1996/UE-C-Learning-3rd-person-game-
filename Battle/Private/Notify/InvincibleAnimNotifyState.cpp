// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/InvincibleAnimNotifyState.h"
#include "Characters/BaseCharacter.h"
#include "Components/CapsuleComponent.h"

void UInvincibleAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (BaseCharacter == nullptr) return;
	BaseCharacter->SetCanBeDamaged(false);
}

void UInvincibleAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (BaseCharacter == nullptr) return;
	BaseCharacter->SetCanBeDamaged(true);
}
