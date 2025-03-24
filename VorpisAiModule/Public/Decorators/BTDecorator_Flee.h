// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_Flee.generated.h"

/**
 * 
 */
UCLASS()
class VORPISAIMODULE_API UBTDecorator_Flee : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTDecorator_Flee();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
