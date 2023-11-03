// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskFindRandomLocation.h"
#include "AI/BaseAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskFindRandomLocation::UBTTaskFindRandomLocation()
{
	NodeName = TEXT("Find Random Location In NavMesh");
}

EBTNodeResult::Type UBTTaskFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseAIController* const BaseAIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (BaseAIController == nullptr) return EBTNodeResult::Failed;
	APawn* Pawn = BaseAIController->GetPawn();
	if (Pawn == nullptr) return EBTNodeResult::Failed;

	// Get Character Current Location
	FVector const CurrentLocation = Pawn->GetActorLocation();

	// Generate a random location
	UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavigationSystem == nullptr) return EBTNodeResult::Failed;
	FNavLocation NavLocation;
	if (NavigationSystem->GetRandomPointInNavigableRadius(CurrentLocation, SearchRadius, NavLocation))
	{
		// Set to the blackboard fvector key
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NavLocation.Location);
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;


}
