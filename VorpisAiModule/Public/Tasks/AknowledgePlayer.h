// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AknowledgePlayer.generated.h"

/**
 * 
 */

class UBlackboardComponent;

UCLASS()
class VORPISAIMODULE_API UAknowledgePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UAknowledgePlayer(FObjectInitializer const& object_initializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBlackboardComponent* BlackboardComponent;
	
};
