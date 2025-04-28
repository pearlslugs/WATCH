// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_Strafe.h"
#include "Npc/NpcInterface.h"
#include "BlackBoardNames/BlackBoardNames.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Strafe::UBTTask_Strafe()
{
	NodeName = TEXT("Strafe");
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_Strafe::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* ControlledPawnAsActor = OwnerComp.GetAIOwner()->GetPawn();
	if (INpcInterface* NpcInterface = Cast<INpcInterface>(ControlledPawnAsActor))
	{
		OwnerComp.GetAIOwner()->StopMovement();
		NpcInterface->StartStrafing();
		OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsEnum(BBKeys::AiCombatState, 13);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
