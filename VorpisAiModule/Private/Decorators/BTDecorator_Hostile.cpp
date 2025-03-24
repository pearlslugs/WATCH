// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_Hostile.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_Hostile::UBTDecorator_Hostile()
{
	NodeName = TEXT("Is Hostile");
	bCreateNodeInstance = true;
}

bool UBTDecorator_Hostile::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		uint8 AiMainBehavior = AIController->GetBlackboardComponent()->GetValueAsEnum("AiMainBehavior");
		if (AiMainBehavior == 0) {
			return true;
		}
		else {
			return false;
		}
		
	}
	return false;
}
