// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/AknowledgePlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharacterStateData/CharacterStateEnums.h"
#include "Npc/NpcInterface.h"

// here, we get the npcs personality and set it to the blackbaord
// based on this, the npc will run, talk or fight

UAknowledgePlayer::UAknowledgePlayer(FObjectInitializer const& object_initializer)
{
	NodeName = "Acknowledge Player";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UAknowledgePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BlackboardComponent = OwnerComp.GetBlackboardComponent();
	INpcInterface* InterfaceOwner = Cast<INpcInterface>(OwnerComp.GetAIOwner()->GetPawn());
	if (InterfaceOwner && BlackboardComponent)
	{
		InterfaceOwner->CreateDialogueWidget();
		BlackboardComponent->SetValueAsBool("InDialogue", true);
		//BlackboardComponent->SetValueAsEnum("CombatState", (uint8)5);
		//BlackboardComponent->SetValueAsBool("TargetAknowledged", true);
	}
	return EBTNodeResult::Succeeded;
}
void UAknowledgePlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{}

