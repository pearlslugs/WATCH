// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_IsBusy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoardNames/BlackBoardNames.h"
#include "AIController.h"

//UENUM(BlueprintType)
//enum class EAiCombatState : uint8
//{
//EACS_None UMETA(DisplayName = "None"),							    // 0
//EACS_StartAttacking UMETA(DisplayName = "StartAttacking"),    // 1
//EACS_Attacking UMETA(DisplayName = "Attacking"),			       // 2	
//EACS_StartStrafing UMETA(DisplayName = "StartStrafing"),		 // 3
//EACS_Strafing UMETA(DisplayName = "Strafing"),				    // 4
//EACS_Dodging UMETA(DisplayName = "Dodging"),					    // 5
//EACS_FollowingTarget UMETA(DisplayName = "FollowingTarget"),  // 6
//EACS_HitStunned UMETA(DisplayName = "HitStunned"),				 // 7
//EACS_BlockStunned UMETA(DisplayName = "BlockStunned"),		    // 8
//};



UBTDecorator_IsBusy::UBTDecorator_IsBusy()
{
	NodeName = "Is Busy";
	bCreateNodeInstance = true;
}

bool UBTDecorator_IsBusy::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (BlackboardComponent)
	{
		uint8 CombatState = BlackboardComponent->GetValueAsEnum(BBKeys::AiCombatState);
		if (CombatState == 13 || CombatState == 2 || CombatState == 4 || CombatState == 7 || CombatState == 8) {
			return true;
		}

	}
	return false;
}
