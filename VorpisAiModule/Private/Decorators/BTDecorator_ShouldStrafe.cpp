// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_ShouldStrafe.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoardNames/BlackBoardNames.h"

UBTDecorator_ShouldStrafe::UBTDecorator_ShouldStrafe()
{
	NodeName = TEXT("Should Strafe");
	bCreateNodeInstance = true;
}

bool UBTDecorator_ShouldStrafe::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return false;
	}

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (BlackboardComponent == nullptr)
	{
		return false;
	}
	uint8 CombatState = AIController->GetBlackboardComponent()->GetValueAsEnum(BBKeys::AiCombatState);
	if (CombatState == 12)
	{
		return true;
	}
	return false;
}
