// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskChasePlayer.h"
#include "AI/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTaskChasePlayer::UBTTaskChasePlayer()
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTTaskChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (BaseAIController == nullptr) return EBTNodeResult::Failed;
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(BaseAIController->GetCharacter());
	if (BaseCharacter == nullptr) return EBTNodeResult::Failed;
	BaseCharacter->GetCharacterMovement()->MaxWalkSpeed = 500.f;


	FVector const TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(BaseAIController, TargetLocation);

	NodeResult = EBTNodeResult::Succeeded;
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return NodeResult;
}
