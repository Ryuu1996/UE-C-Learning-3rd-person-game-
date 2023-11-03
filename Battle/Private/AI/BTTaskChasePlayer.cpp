// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskChasePlayer.h"
#include "AI/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTaskChasePlayer::UBTTaskChasePlayer()
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTTaskChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (BaseAIController == nullptr) return EBTNodeResult::Failed;
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(BaseAIController->GetPawn());
	if (BaseCharacter == nullptr) return EBTNodeResult::Failed;
	BaseCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.f;


	FVector const TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(BaseAIController, TargetLocation);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
