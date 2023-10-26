// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/OccupyAnimNotifyState.h"
#include "Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Enums/CharacterEnums.h"


void UOccupyAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (PlayerCharacter == nullptr) return;
	PlayerCharacter->SetCharacterActionState(ECharacterActionState::Occupied);
}

void UOccupyAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (PlayerCharacter == nullptr) return;
	PlayerCharacter->SetCharacterActionState(ECharacterActionState::Unoccupied);
}
