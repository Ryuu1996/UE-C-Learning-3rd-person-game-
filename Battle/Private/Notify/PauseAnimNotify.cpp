// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/PauseAnimNotify.h"
#include "Characters/BaseCharacter.h"

void UPauseAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;
	ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (Character == nullptr) return;
	Character->GetMesh()->GetAnimInstance()->Montage_Pause();
	
}
