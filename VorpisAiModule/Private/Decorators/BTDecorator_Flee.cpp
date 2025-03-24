// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_Flee.h"
#include "AIController.h"
#include "BlackBoardNames/BlackBoardNames.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_Flee::UBTDecorator_Flee()
{
	NodeName = TEXT("Is Fleeing");
	bCreateNodeInstance = true;
}

bool UBTDecorator_Flee::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		uint8 AiMainBehavior = AIController->GetBlackboardComponent()->GetValueAsEnum(BBKeys::AiMainBehavior);
		if (AiMainBehavior == 1) {
			return true;
		}
		else {
			return false;
		}

	}
	return false;
}
