// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "BaseCharacter.generated.h"

UCLASS()
class BATTLE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
private:
public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/********************
	* Initialize Functions
	********************/
	// Initialize Character properties
	virtual void InitializeCharacterProperties();

	// Initialize Character states
	virtual void InitializeChracterStates();

private:

};
