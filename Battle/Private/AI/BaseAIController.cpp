// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"
#include "Characters/BaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Characters/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer)
{
	SetupPerceptionSystem();
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ABaseCharacter* const BaseCharacter = Cast<ABaseCharacter>(InPawn);
	if (BaseCharacter == nullptr) return;

	// Get behavior tree of the character
	UBehaviorTree* const BehaviorTree = BaseCharacter->GetBehaviorTree();
	if (BehaviorTree == nullptr) return;

	// Set the blackboard to use the blackboard assets of the character tree
	UBlackboardComponent* BlackboardComponent;
	UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);
	Blackboard = BlackboardComponent;

	// Run the tree
	RunBehaviorTree(BehaviorTree);
}

void ABaseAIController::SetupPerceptionSystem()
{
	// Create sight perception system
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig == nullptr) return;
	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
	SightConfig->PeripheralVisionAngleDegrees = 45.f;
	SightConfig->SetMaxAge(5.f); // The time of the perceived stimulus forgotten
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;


	// Set current perception component
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAIController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);

	
}

void ABaseAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	APlayerCharacter* const PlayerCharacter = Cast<APlayerCharacter>(Actor);
	if (PlayerCharacter == nullptr) return;
	GetBlackboardComponent()->SetValueAsBool(FName("CanSeePlayer"), Stimulus.WasSuccessfullySensed());

}
