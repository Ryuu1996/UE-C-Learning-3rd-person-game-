// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskFindPlayerLocation.generated.h"

/**
 *
 */
UCLASS()
class BATTLE_API UBTTaskFindPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
private:
	float ChaseRadius = 50.f;
public:
	UBTTaskFindPlayerLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
