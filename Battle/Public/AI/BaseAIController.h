// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"

#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
private:
	// Configuration used to set up the sight system
	class UAISenseConfig_Sight* SightConfig;
public:
	ABaseAIController(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

};
