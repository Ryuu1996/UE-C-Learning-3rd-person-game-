// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskPatrolTo.h"
#include "AI/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTaskPatrolTo::UBTTaskPatrolTo(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Patrol To";
}

EBTNodeResult::Type UBTTaskPatrolTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	ABaseAIController* BaseAIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (BaseAIController == nullptr) return EBTNodeResult::Failed;
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(BaseAIController->GetPawn());
	if (BaseCharacter == nullptr) return EBTNodeResult::Failed;
	BaseCharacter->GetCharacterMovement()->MaxWalkSpeed = 100.f;

	NodeResult = Super::ExecuteTask(OwnerComp, NodeMemory);
	return NodeResult;
}
