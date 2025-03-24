// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_ShouldStrafe.generated.h"

/**
 * 
 */
UCLASS()
class VORPISAIMODULE_API UBTDecorator_ShouldStrafe : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTDecorator_ShouldStrafe();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
