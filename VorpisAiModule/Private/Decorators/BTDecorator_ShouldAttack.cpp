// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_ShouldAttack.h"
#include "AIController.h"
#include "BlackBoardNames/BlackBoardNames.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_ShouldAttack::UBTDecorator_ShouldAttack()
{
	NodeName = TEXT("Should Attack");
	bCreateNodeInstance = true;
}

bool UBTDecorator_ShouldAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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

	int MaxHitCounter = BlackboardComponent->GetValueAsInt(BBKeys::MaxHitCounter);
	int HitCounter = BlackboardComponent->GetValueAsInt(BBKeys::HitCounter);
	uint8 CombatState = BlackboardComponent->GetValueAsEnum(BBKeys::AiCombatState);

	if (CombatState == 1 && MaxHitCounter >= HitCounter)
	{
		return true;
	}
	return false;
}
