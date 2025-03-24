// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SplinePath/VorpisSplinePath.h"
#include "BTTask_FollowSplinePath.generated.h"

/**
 * 
 */

class ANpcController;

UCLASS()
class VORPISAIMODULE_API UBTTask_FollowSplinePath : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_FollowSplinePath();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UFUNCTION()
	void SetSplinePath(AVorpisSplinePath* SplinePathToSet) { VorpisSplinePath = SplinePathToSet; }
	UFUNCTION()
	AVorpisSplinePath* GetSplinePath() { return VorpisSplinePath; }
	UFUNCTION()
	void SetControlledPawn(APawn* PawnToSet) { ControlledPawn = PawnToSet; }
	UFUNCTION()
	APawn* GetControlledPawn() { return ControlledPawn;}

	UPROPERTY()
	FSplinePath CurrentPath;

	protected:
	UPROPERTY(EditAnywhere, Category = "Spline Path")
	AVorpisSplinePath* VorpisSplinePath = nullptr;
	UPROPERTY(EditAnywhere, Category = "Controlled Pawn")
	APawn* ControlledPawn;
	UPROPERTY(EditAnywhere, Category = "Spline Path")
	ANpcController* NpcController;
	
	
};
