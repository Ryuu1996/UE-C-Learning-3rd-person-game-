// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Enums/CharacterEnums.h"

#include "LocomotionAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API ULocomotionAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	// Character current speed
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float CharacterSpeed = 0.f;

	// Character current direction
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float CharacterDirection = 0.f;

	// Is character falling
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool IsFalling = false;

	// Is character crouching
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool IsCrouching = false;



public:

protected:
	// Initialize base variables
	virtual void NativeInitializeAnimation() override;

	// Update variables
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	class ACharacter* CharacterOwner;
private:

public:
	FORCEINLINE bool GetIsCrouching() const { return IsCrouching; }
	FORCEINLINE void SetIsCrouching(bool Result) { IsCrouching = Result; }




};
