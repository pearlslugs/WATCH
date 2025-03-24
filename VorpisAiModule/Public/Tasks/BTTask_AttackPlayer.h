// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class VORPISAIMODULE_API UBTTask_AttackPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_AttackPlayer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	float AttackRange = 360.0f;
	
};
