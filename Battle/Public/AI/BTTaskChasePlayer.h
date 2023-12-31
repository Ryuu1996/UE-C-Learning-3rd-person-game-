// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_API UBTTaskChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
private:
public:
	UBTTaskChasePlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
