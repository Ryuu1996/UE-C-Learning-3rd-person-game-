// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskFindPlayerLocation.h"
#include "Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/BaseAIController.h"

UBTTaskFindPlayerLocation::UBTTaskFindPlayerLocation()
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTTaskFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APlayerCharacter* const PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter == nullptr) return EBTNodeResult::Failed;
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (BaseAIController == nullptr) return EBTNodeResult::Failed;
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(BaseAIController->GetCharacter());
	if (BaseCharacter == nullptr) return EBTNodeResult::Failed;

	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	FVector CharacterLocation = BaseCharacter->GetActorLocation();
	FVector NormalizeVector = (CharacterLocation - PlayerLocation).GetSafeNormal();
	FVector TargetLocation = TargetLocation = PlayerLocation + NormalizeVector * ChaseRadius;

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);
	return EBTNodeResult::Succeeded;


}
