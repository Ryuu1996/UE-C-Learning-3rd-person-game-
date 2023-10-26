// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/LocomotionAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"

void ULocomotionAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	CharacterOwner = Cast<ACharacter>(TryGetPawnOwner());
}

void ULocomotionAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (CharacterOwner == nullptr) return;
	UCharacterMovementComponent* CharacterMovementComponent = CharacterOwner->GetCharacterMovement();
	CharacterSpeed = UKismetMathLibrary::VSizeXY(CharacterMovementComponent->Velocity);
	CharacterDirection = UKismetAnimationLibrary::CalculateDirection(CharacterMovementComponent->Velocity, CharacterOwner->GetActorRotation());
	IsFalling = CharacterMovementComponent->IsFalling();
}
