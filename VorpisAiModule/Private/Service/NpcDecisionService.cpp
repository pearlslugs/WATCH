// Fill out your copyright notice in the Description page of Project Settings.


#include "Service/NpcDecisionService.h"
#include "Npc/NpcController.h"
#include "BlackBoardNames/BlackBoardNames.h"
#include "BehaviorTree/BlackboardComponent.h"


//enum class EAiMainBehavior : uint8
//{
//	AMB_Fighting UMETA(DisplayName = "Fighting"),				    // 0
//	AMB_Fleeing UMETA(DisplayName = "Fleeing"),					    // 1
//	AMB_Hiding UMETA(DisplayName = "Hiding"),					       // 2
//	AMB_Surrendering UMETA(DisplayName = "Surrendering"),			 // 3
//	AMB_Manipulating UMETA(DisplayName = "Manipulating"),			 // 4
//};
//
//UENUM(BlueprintType)
//enum class EAiCombatState : uint8
//{
//EACS_None UMETA(DisplayName = "None"),							    // 0
//EACS_StartAttacking UMETA(DisplayName = "StartAttacking"),    // 1
//EACS_Attacking UMETA(DisplayName = "Attacking"),			       // 2	
//EACS_StartStrafing UMETA(DisplayName = "StartStrafing"),		 // 3
//EACS_Strafing UMETA(DisplayName = "Strafing"),				    // 4
//EACS_Dodging UMETA(DisplayName = "Dodging"),					    // 5
//EACS_FollowingTarget UMETA(DisplayName = "FollowingTarget"),  // 6
//EACS_HitStunned UMETA(DisplayName = "HitStunned"),				 // 7
//EACS_BlockStunned UMETA(DisplayName = "BlockStunned"),		    // 8
//};

UNpcDecisionService::UNpcDecisionService(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("NPCDecisionMaker");
	ControlledPawn = nullptr;
	OwnerBlackboard = nullptr;
	NpcController = nullptr;
	Interval = 0.12f;
	bCreateNodeInstance = true;
}


void UNpcDecisionService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (NpcController == nullptr || GetBlackboardComponent() == nullptr || !IsValid(ControlledPawn))
	{
		SetBlackboardComponent(OwnerComp.GetBlackboardComponent());
		ANpcController* NewController = Cast<ANpcController>(OwnerComp.GetAIOwner());
		SetNpcController(NewController);
		SetControlledPawn(NewController->GetPawn());
	}
	
	uint8 EnemyBehavior = GetBlackboardComponent()->GetValueAsEnum(BBKeys::AiMainBehavior);
	uint8 CombatState = GetBlackboardComponent()->GetValueAsEnum(BBKeys::AiCombatState);
	if (CombatState == 2 || CombatState == 3 || CombatState == 4 || CombatState == 5
		|| CombatState == 7 || CombatState == 8) {
		
	}
	else {
		// print combat state
		AActor* Target = Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(BBKeys::Target));
		if (IsValid(Target))
		{
			float Distance = FVector::Dist(ControlledPawn->GetActorLocation(), Target->GetActorLocation());
			if (Distance > AttackDistance)
			{
				GetBlackboardComponent()->SetValueAsEnum(BBKeys::AiCombatState, 6);
			}
			else
			{
				float Random = FMath::FRandRange(0.0f, 1.0f);
				if (Random <= 0.5f)
				{
					GetBlackboardComponent()->SetValueAsEnum(BBKeys::AiCombatState, 1);
				}
				else
				{
					GetBlackboardComponent()->SetValueAsEnum(BBKeys::AiCombatState, 3);
				}
			}
		}

		// if ai behvior is combat
			// if far from player
			  // follow player, set blackboard combat state to follow
		// if close to player
		  // if player is close and angle is right
			 // attack player or strafe
			 // use max strafe time and max strafe amount as well as agressivness to determine
			 // maybe kick smetimes
		// if health is low
		  // run away or surrender
		// if player health is low
		  // maybe offer mercy
	}
}