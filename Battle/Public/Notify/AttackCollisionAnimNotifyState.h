// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackCollisionAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API UAttackCollisionAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
private:
public:
protected:
private:
	// Notify Begin
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	// Notify End
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
