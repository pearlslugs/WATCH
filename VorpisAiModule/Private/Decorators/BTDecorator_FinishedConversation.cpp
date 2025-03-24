// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_FinishedConversation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoardNames/BlackBoardNames.h"
#include "AIController.h"

UBTDecorator_FinishedConversation::UBTDecorator_FinishedConversation()
{
	NodeName = "Finished Conversation";
	bCreateNodeInstance = true;
}

bool UBTDecorator_FinishedConversation::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == nullptr)
	{
		return false;
	}

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return false;
	}

	// Get the value of the blackboard key
	bool IsInDialogue = BlackboardComp->GetValueAsBool(BBKeys::InDialogue);
	bool TargetAknowledged = BlackboardComp->GetValueAsBool(BBKeys::TargetAknowledged);
	if (!IsInDialogue && TargetAknowledged)
	{
		return true;
	}

	return false;
}
