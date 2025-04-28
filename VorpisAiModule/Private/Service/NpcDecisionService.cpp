// Fill out your copyright notice in the Description page of Project Settings.


#include "Service/NpcDecisionService.h"
#include "Npc/NpcController.h"
#include "BlackBoardNames/BlackBoardNames.h"
#include "BehaviorTree/BlackboardComponent.h"

// need ot  start usng this if i am not
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

//UENUM(BlueprintType)
//enum class ECombatState : uint8
//{
//	ECS_None UMETA(DisplayName = "None"),									// 0
//	ECS_StartAttacking UMETA(DisplayName = "StartAttacking"),		// 1
//	ECS_Attacking UMETA(DisplayName = "Attacking"),						// 2
//	ECS_ShieldBlocking UMETA(DisplayName = "ShieldBlocking"),		// 3
//	ECS_Dodging UMETA(DisplayName = "Dodging"),							// 4
//	ECS_Aiming UMETA(DisplayName = "Aiming"),								// 5
//	ECS_Reloading UMETA(DisplayName = "Reloading"),						// 6
//	ECS_Throwing UMETA(DisplayName = "Throwing"),						// 7
//	ECS_Kicking UMETA(DisplayName = "Kicking"),							// 8
//	ECS_Parrying UMETA(DisplayName = "Parrying"),						// 9
//	ECS_HitStunned UMETA(DisplayName = "HitStunned"),					// 10
//	ECS_BlockStunned UMETA(DisplayName = "BlockStunned"),				// 11
//	ECS_StartStrafing UMETA(DisplayName = "StartStrafing"),			// 12
//	ECS_Strafing UMETA(DisplayName = "Strafing"),						// 13
//	EACS_FollowingTarget UMETA(DisplayName = "FollowingTarget"),	// 14
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
	// it keeps getting stuck, it was on follow player, but just standing there
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
	// if stuck strafing or attacking
	// all of the below logic should only be if they are fighting
	// make combat logic funciton to call
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::FromInt((int)CombatState));
	}
	if (CombatState == 2 || CombatState == 13 || CombatState == 5) {
		if (!TimerCalled)
		{
			TimerCalled = true;
			GetWorld()->GetTimerManager().SetTimer(FreeUpNpcTimer, this, &UNpcDecisionService::FreeUpCharacter, FreeUpNpcTimerRate, false);
		}
	}
	// dont reset if starting strafe or starting attack
	if (CombatState == 1 || CombatState == 12 || CombatState == 4
		|| CombatState == 10 || CombatState == 11)
	{
		// dont return, it messes up
	}
	else {
		// print combat state
		AActor* Target = Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(BBKeys::Target));
		if (IsValid(Target)) {
			float Distance = FVector::Dist(ControlledPawn->GetActorLocation(), Target->GetActorLocation());
			if (Distance > AttackDistance) {
				GetBlackboardComponent()->SetValueAsEnum(BBKeys::AiCombatState, 14);
			}
			else {
				float Random = FMath::FRandRange(0.0f, 1.0f);
				bool OnStrafeCoolDown = GetBlackboardComponent()->GetValueAsBool(BBKeys::OnStrafeCoolDown);
				bool OnCoolDown = GetBlackboardComponent()->GetValueAsBool(BBKeys::OnAtackCoolDown);
				if (OnStrafeCoolDown) {
					// if we are  on strafe cool down
					GetBlackboardComponent()->SetValueAsBool(BBKeys::OnAtackCoolDown, false);
					GetBlackboardComponent()->SetValueAsEnum(BBKeys::AiCombatState, 1);
				} else if (Random < 0.70f && !OnCoolDown) {
					GetBlackboardComponent()->SetValueAsEnum(BBKeys::AiCombatState, 1);
				}
				else {
					GetBlackboardComponent()->SetValueAsBool(BBKeys::OnStrafeCoolDown, true);
					GetBlackboardComponent()->SetValueAsEnum(BBKeys::AiCombatState, 12);
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

void UNpcDecisionService::FreeUpCharacter()
{
	uint8 CombatState = GetBlackboardComponent()->GetValueAsEnum(BBKeys::AiCombatState);
	if (CombatState == 2 || CombatState == 13 || CombatState == 5)
	{

		GetBlackboardComponent()->SetValueAsEnum(BBKeys::AiCombatState, 0);
		GetBlackboardComponent()->SetValueAsBool(BBKeys::OnAtackCoolDown, false);
	}
	TimerCalled = false;
}
