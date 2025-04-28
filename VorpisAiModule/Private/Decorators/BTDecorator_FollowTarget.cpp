// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_FollowTarget.h"
#include "AIController.h"
#include "BlackBoardNames/BlackBoardNames.h"
#include "BehaviorTree/BlackboardComponent.h"


//UENUM(BlueprintType)
//enum class ECombatState : uint8
//{
//	ECS_None UMETA(DisplayName = "None"),									// 0
//	ECS_StartAttacking UMETA(DisplayName = "StartAttacking"),		// 1
//	ECS_Attacking UMETA(DisplayName = "Attacking"),						// 2
//	ECS_ShieldBlocking UMETA(DisplayName = "ShieldBlocking"),		// 3
//	ECS_Dodging UMETA(DisplayName = "Dodging"),							// 4
//	ECS_Aiming UMETA(DisplayName = "Aiming"),								// 5
//	ECS_Reloading UMETA(DisplayName = "Reloading"),						// 6
//	ECS_Throwing UMETA(DisplayName = "Throwing"),						// 7
//	ECS_Kicking UMETA(DisplayName = "Kicking"),							// 8
//	ECS_Parrying UMETA(DisplayName = "Parrying"),						// 9
//	ECS_HitStunned UMETA(DisplayName = "HitStunned"),					// 10
//	ECS_BlockStunned UMETA(DisplayName = "BlockStunned"),				// 11
//	ECS_StartStrafing UMETA(DisplayName = "StartStrafing"),			// 12
//	ECS_Strafing UMETA(DisplayName = "Strafing"),						// 13
//	EACS_FollowingTarget UMETA(DisplayName = "FollowingTarget"),	// 14
//};

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
		if (CombatState == 14)
		{
			return true;
		}
	}
	return false;
}