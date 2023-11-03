// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTaskPatrolTo.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API UBTTaskPatrolTo : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	UBTTaskPatrolTo(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
