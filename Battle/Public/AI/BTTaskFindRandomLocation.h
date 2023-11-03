// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskFindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API UBTTaskFindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, Category = "TOSET AI")
	float SearchRadius = 1500.f;
public:
	UBTTaskFindRandomLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
