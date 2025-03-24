// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_Hide.h"
#include "AIController.h"
#include "BlackBoardNames/BlackBoardNames.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_Hide::UBTDecorator_Hide()
{
	NodeName = TEXT("Is Hiding");
	bCreateNodeInstance = true;
}

bool UBTDecorator_Hide::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		uint8 AiMainBehavior = AIController->GetBlackboardComponent()->GetValueAsEnum(BBKeys::AiMainBehavior);
		if (AiMainBehavior == 3) {
			return true;
		}
		else {
			return false;
		}

	}
	return false;
}