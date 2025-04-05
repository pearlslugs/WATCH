// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "NpcDecisionService.generated.h"

/**
 * 
 */

class APawn;
class UBlackboardComponent;
class ANpcController;

UCLASS()
class VORPISAIMODULE_API UNpcDecisionService : public UBTService
{
	GENERATED_BODY()
public:

	FTimerHandle FreeUpNpcTimer;
	float FreeUpNpcTimerRate = 3.f;
	bool TimerCalled = false;

	UNpcDecisionService(const FObjectInitializer& ObjectInitializer);
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	UFUNCTION()
	void SetControlledPawn(APawn* Pawn) { ControlledPawn = Pawn; }
	UFUNCTION()
	APawn* GetControlledPawn() { return ControlledPawn; }
	UFUNCTION()
	void SetBlackboardComponent(UBlackboardComponent* Blackboard) { OwnerBlackboard = Blackboard; }
	UFUNCTION()
	UBlackboardComponent* GetBlackboardComponent() { return OwnerBlackboard; }
	UFUNCTION()
	void SetNpcController(ANpcController* Controller) { NpcController = Controller; }
	UFUNCTION()
	ANpcController* GetNpcController() { return NpcController; }
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NpcService")
	float AttackDistance = 355.f;

	UFUNCTION()
	void FreeUpCharacter();


protected:
	UPROPERTY()
	APawn* ControlledPawn;	
	UPROPERTY()
	UBlackboardComponent* OwnerBlackboard;
	UPROPERTY()
	ANpcController* NpcController;
	
};
