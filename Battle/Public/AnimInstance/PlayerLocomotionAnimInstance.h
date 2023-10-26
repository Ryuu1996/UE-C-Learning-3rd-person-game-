// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/LocomotionAnimInstance.h"
#include "PlayerLocomotionAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API UPlayerLocomotionAnimInstance : public ULocomotionAnimInstance
{
	GENERATED_BODY()

private:
	// Player Character
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	// Character equip state
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	ECharacterEquipState CharacterState;


public:

protected:
	// Initialize base variables
	virtual void NativeInitializeAnimation() override;

	// Update variables
	virtual void NativeUpdateAnimation(float DeltaTime) override;
private:
};
