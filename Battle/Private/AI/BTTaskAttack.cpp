// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskAttack.h"
#include "AI/BaseAIController.h"
#include "Characters/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTTaskAttack::UBTTaskAttack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	if (BaseAIController == nullptr) return EBTNodeResult::Failed;
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(BaseAIController->GetCharacter());
	if (EnemyCharacter == nullptr) return EBTNodeResult::Failed;
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(EnemyCharacter->GetActorLocation(), PlayerCharacter->GetActorLocation());
	EnemyCharacter->SetActorRotation(LookAtRotation, ETeleportType::None);

	if (PlayerCharacter->GetCurrentHP() > 0)
		EnemyCharacter->Attack();
	else
		BaseAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsInCombat"), false);
	NodeResult = EBTNodeResult::Succeeded;
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return NodeResult;
}
