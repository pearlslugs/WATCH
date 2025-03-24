// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTTask_FollowPlayer.generated.h"

/**
 * 
 */
UCLASS()
class VORPISAIMODULE_API UBTTask_FollowPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_FollowPlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UBlackboardComponent* BlackboardComponent = nullptr;
	
};
