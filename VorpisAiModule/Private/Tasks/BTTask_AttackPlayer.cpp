// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_AttackPlayer.h"
#include "AIController.h"
#include "Npc/NpcInterface.h"
#include "BlackBoardNames/BlackBoardNames.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_AttackPlayer::UBTTask_AttackPlayer()
{
	NodeName = TEXT("Attack Player");
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
		// Get the AI controller
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AActor* ControlledPawnAsActor = AIController->GetPawn();
	Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (Target == nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(BBKeys::AiCombatState, 0);
		return EBTNodeResult::Failed;
	}
	else if (IsValid(Target)) {
		float Distance = FVector::Distance(AIController->GetPawn()->GetActorLocation(), Target->GetActorLocation());
		//float AngleToPlayer = FVector::DotProduct(AIController->GetPawn()->GetActorForwardVector(), (Target->GetActorLocation() - AIController->GetPawn()->GetActorLocation()).GetSafeNormal());
		if (Distance > AttackRange)
		{
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "should switch to none");
			}
			OwnerComp.GetBlackboardComponent()->SetValueAsEnum(BBKeys::AiCombatState, 0);
		}
		if (INpcInterface* NpcInterface = Cast<INpcInterface>(ControlledPawnAsActor))
		{
			AIController->StopMovement();
			NpcInterface->InterfaceAttack();
		}
		return EBTNodeResult::Succeeded;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(BBKeys::AiCombatState, 0);
	return EBTNodeResult::Failed;
	
}