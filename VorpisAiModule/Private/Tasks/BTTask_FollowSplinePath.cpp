// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_FollowSplinePath.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Npc//NpcInterface.h"
#include "Npc/NpcController.h"
#include "SplinePath/VorpisSplinePath.h"

UBTTask_FollowSplinePath::UBTTask_FollowSplinePath()
{
	NodeName = TEXT("Follow Spline Path");
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_FollowSplinePath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!VorpisSplinePath) {
		INpcInterface* NpcInterface = Cast<INpcInterface>(OwnerComp.GetAIOwner()->GetPawn());
		if (NpcInterface) {
			SetSplinePath(Cast<AVorpisSplinePath>(NpcInterface->GetSplinePathAsActor()));
			CurrentPath = VorpisSplinePath->SplinePath;
		}
		return EBTNodeResult::Succeeded;
	}
	if (VorpisSplinePath) {
		if (CurrentPath.IsFinished) {
			// we need to set the blackboard variable to true
			return EBTNodeResult::Succeeded;
		}
		if (VorpisSplinePath->GetCurrentSplineComponent())
		{
			FVector NextPointLocation = VorpisSplinePath->SplineComponents[CurrentPath.CurrentPathGuid]->GetWorldLocationAtSplinePoint(CurrentPath.CurrentPointOnPath);
			if (NextPointLocation == FVector::ZeroVector) {
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
			if (!NpcController) {
				NpcController = Cast<ANpcController>(OwnerComp.GetAIOwner());
				return EBTNodeResult::Succeeded;
			}
			if (NpcController) 
			{
				NpcController->MoveToLocation(NextPointLocation, .0f);
				if (NpcController->GetPawn()->GetActorLocation().Equals(NextPointLocation, 95.0f)) {
					CurrentPath.GoToNextPoint();
				}
			}
			else
			{
			}
		}
	}
	return EBTNodeResult::Succeeded;
}

void UBTTask_FollowSplinePath::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

};