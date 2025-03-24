// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_FollowTarget.h"
#include "AIController.h"
#include "BlackBoardNames/BlackBoardNames.h"
#include "BehaviorTree/BlackboardComponent.h"


///////////////////////////////////////////////////////////////////
//  EACS_None UMETA(DisplayName = "None"),							  // 0
//  EACS_StartAttacking UMETA(DisplayName = "StartAttacking"),   // 1
//  EACS_Attacking UMETA(DisplayName = "Attacking"),			     // 2	
//  EACS_Strafing UMETA(DisplayName = "Strafing"),				     // 3
//  EACS_Dodging UMETA(DisplayName = "Dodging"),					  // 4
//  EACS_FollowingTarget UMETA(DisplayName = "FollowingTarget"), // 5 <==== if its 5 then follow target
///////////////////////////////////////////////////////////////////

UBTDecorator_FollowTarget::UBTDecorator_FollowTarget()
{
	NodeName = TEXT("Follow Target");
	bCreateNodeInstance = true;
}

bool UBTDecorator_FollowTarget::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		uint8 CombatState = AIController->GetBlackboardComponent()->GetValueAsEnum(BBKeys::AiCombatState);
		if (CombatState == 6)
		{
			return true;
		}
	}
	return false;
}