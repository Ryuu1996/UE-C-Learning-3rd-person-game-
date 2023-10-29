// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/OccupyAnimNotifyState.h"
#include "Characters/BaseCharacter.h"
#include "Enums/CharacterEnums.h"


void UOccupyAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;
	ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (Character == nullptr) return;
	Character->SetCharacterActionState(ECharacterActionState::Occupied);
}

void UOccupyAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;
	ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (Character == nullptr) return;
	Character->SetCharacterActionState(ECharacterActionState::Unoccupied);
}
