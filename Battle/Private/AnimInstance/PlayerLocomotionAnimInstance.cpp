// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/PlayerLocomotionAnimInstance.h"
#include "Characters/PlayerCharacter.h"



void UPlayerLocomotionAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
}

void UPlayerLocomotionAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (PlayerCharacter == nullptr) return;
	CharacterState = PlayerCharacter->GetCharacterEquipState();
}
