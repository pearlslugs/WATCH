// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_FollowPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoardNames/BlackBoardNames.h"
#include "AIController.h"

UBTTask_FollowPlayer::UBTTask_FollowPlayer()
{
	NodeName = TEXT("Follow Player");
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_FollowPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!BlackboardComponent)
	{
		BlackboardComponent = OwnerComp.GetBlackboardComponent();
	}
	if (BlackboardComponent)
	{
		APawn* PlayerPawn = Cast<APawn>(BlackboardComponent->GetValueAsObject("Target"));
		APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
		float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), ControlledPawn->GetActorLocation());
		if (PlayerPawn && Distance > 200.f)
		{
			OwnerComp.GetAIOwner()->MoveToActor(PlayerPawn);
			return EBTNodeResult::InProgress;
		}
		else if (Distance <= 200.f)
		{
			// we need to let the black board know its time to attack or strafe
			BlackboardComponent->SetValueAsEnum(BBKeys::AiCombatState, 0);
			return EBTNodeResult::InProgress;
		}
	}
	return EBTNodeResult::InProgress;
}