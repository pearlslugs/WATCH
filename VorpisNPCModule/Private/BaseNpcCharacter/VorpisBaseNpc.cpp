// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNpcCharacter/VorpisBaseNpc.h"
#include "Perception/AISense_Sight.h"
#include "NpcDialogue/NpcDialogueComponent.h"
#include "MontageManagerComponent/MontageManagerComponent.h"
#include "CharacterStateData/CharacterStateEnums.h"
#include "Kismet/KismetMathLibrary.h"
#include "GeneralData/GeneralData.h"
#include "PlayerCharacter/VorpisPlayerCharacterInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

AVorpisBaseNpc::AVorpisBaseNpc()
{
	PrimaryActorTick.bCanEverTick = true;
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	NpcDialogueComponent = CreateDefaultSubobject<UNpcDialogueComponent>(TEXT("NpcDialogueComponent"));
	AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
	SplinePathActor = nullptr;
	AIController = nullptr;
	TargetActor = nullptr;
	AllStrafeDirections.Add(EStrafingMovementDirection::ESMD_Left);
	AllStrafeDirections.Add(EStrafingMovementDirection::ESMD_Right);
	AllStrafeDirections.Add(EStrafingMovementDirection::ESMD_Backward);
}

void AVorpisBaseNpc::BeginPlay()
{
	Super::BeginPlay();
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AVorpisBaseNpc::OnTargetPerceptionUpdated);
	AIController = Cast<AAIController>(GetController());

	ResetAvailableStrafeDirections();
}

void AVorpisBaseNpc::OnTargetPerceptionUpdated(AActor* PercievedActor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (AIController)
		{
			IVorpisPlayerCharacterInterface* PlayerCharacter = Cast<IVorpisPlayerCharacterInterface>(PercievedActor);
			if (PlayerCharacter)
			{
				// get team
				GetBlackboardComponent()->SetValueAsObject("Target", PercievedActor); // We will need to expand this if there are gonna be non enemies
				TargetActor = PercievedActor;
				AIController->StopMovement();
			}
		}
		else {
			AIController = Cast<AAIController>(GetController());
		}
	}
	else
	{
	}
}

void AVorpisBaseNpc::FinishDialogue(EDialogueOutcome Outcome)
{
	GetBlackboardComponent()->SetValueAsBool("InDialogue", false);
	return;
}

void AVorpisBaseNpc::CreateDialogueWidget()
{
	NpcDialogueComponent->BeginDialogue();
}

void AVorpisBaseNpc::Attack()
{
	if (AttackStarted) return;
	bool OnAttackCoolDown = GetBlackboardComponent()->GetValueAsBool("OnAtackCoolDown");
	if (OnAttackCoolDown) {
		if (!GetWorld()->GetTimerManager().IsTimerActive(ResetAttackCoooldownTimer)) {
			GetWorld()->GetTimerManager().SetTimer(ResetAttackCoooldownTimer, this, &AVorpisBaseNpc::ResetAttackCooldown, ResetAttackCooldownTime, false);
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "On Cool Down");
		GetBlackboardComponent()->SetValueAsEnum("CombatState", (uint8)0);
		GetBlackboardComponent()->SetValueAsInt("HitCounter", 0);
		return;
	}
	uint8 CurrentCombatState = GetBlackboardComponent()->GetValueAsEnum("CombatState");
	FString CombatState = FString::FromInt(CurrentCombatState);
	if (CurrentCombatState != (uint8)EAiCombatState::EACS_StartAttacking)
	{
		return;
	}
	GetBlackboardComponent()->SetValueAsEnum("CombatState", (uint8)EAiCombatState::EACS_Attacking);
	int Combo = 0;
	int MaxHitCounter = GetBlackboardComponent()->GetValueAsInt("MaxHitCounter");
	int HitCounter = GetBlackboardComponent()->GetValueAsInt("HitCounter");
	if (HitCounter > MaxHitCounter) {
		StartAttackCoolDown();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "hit max reached");
		// he should strafe, dodge or stand his ground
		// right now he goes back to the idle state
		GetBlackboardComponent()->SetValueAsInt("HitCounter", 0);
		AIController->GetBlackboardComponent()->SetValueAsEnum("CombatState", (uint8)EAiCombatState::EACS_None);
	}
	AttackStarted = true;
	ECombatPosition Position = CombatComponent->GetCombatPosition();
	if (Position == ECombatPosition::ECP_High) {
		Combo = CombatComponent->GetComboCount();
	}
	UAnimMontage* Montage = MontageManagerComponent->GetAttackMontage(Position, false, Combo);
	if (IsValid(Montage)) {
		CombatComponent->IncrimentComboCount();
		PlayAnimMontage(Montage);
		GetBlackboardComponent()->SetValueAsInt("HitCounter", HitCounter + 1);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Good");
	}
}

void AVorpisBaseNpc::StartAttackCoolDown()
{
	GetBlackboardComponent()->SetValueAsEnum("CombatState", (uint8)EAiCombatState::EACS_None);
	GetBlackboardComponent()->SetValueAsBool("OnAtackCoolDown", true);
	GetBlackboardComponent()->SetValueAsInt("HitCounter", 0);
	GetWorld()->GetTimerManager().SetTimer(ResetAttackCoooldownTimer, this, &AVorpisBaseNpc::ResetAttackCooldown, ResetAttackCooldownTime, false);
}

void AVorpisBaseNpc::ResetAttackCooldown()
{
	GetBlackboardComponent()->SetValueAsBool("OnAtackCoolDown", false);
	GetBlackboardComponent()->SetValueAsInt("HitCounter", 0);
}

void AVorpisBaseNpc::InterfaceAttack()
{
	// slightly delay for checking state change
	AVorpisBaseNpc::Attack();
}

void AVorpisBaseNpc::StartStrafing()
{
	RandomlyAssignStrafeDirection();
	AvailableStrafeDirections.Remove(CurrentStrafeDirection);
	Strafe();
}

void AVorpisBaseNpc::RandomlyAssignStrafeDirection()
{
	if (AvailableStrafeDirections.Num() == 0)
	{
		ResetAvailableStrafeDirections();
		return;
	}
	CurrentStrafeDirection = AvailableStrafeDirections[FMath::RandRange(0, AvailableStrafeDirections.Num() - 1)];
}

void AVorpisBaseNpc::ResetAvailableStrafeDirections()
{
	AvailableStrafeDirections.Empty();
	AvailableStrafeDirections.Append(AllStrafeDirections);
	GetBlackboardComponent()->SetValueAsFloat("StrafeTime", 0.0f);
	GetBlackboardComponent()->SetValueAsEnum("CombatState", (uint8)EAiCombatState::EACS_None);
}

UBlackboardComponent* AVorpisBaseNpc::GetBlackboardComponent()
{
	return AIController->GetBlackboardComponent();
}

void AVorpisBaseNpc::StopStrafing()
{}

void AVorpisBaseNpc::Strafe()
{
	if (!GEngine) {
		return;
	}
	float CurrentStrafeTime = GetBlackboardComponent()->GetValueAsFloat("StrafeTime");
	float MaxStrafeTime = GetBlackboardComponent()->GetValueAsFloat("MaxStrafeTime");
	AActor* Target = Cast<AActor>(GetBlackboardComponent()->GetValueAsObject("Target"));
	float DistanceToTarget = FVector::Dist(GetActorLocation(), Target->GetActorLocation());
	if (DistanceToTarget > 1400)
	{
		ResetAvailableStrafeDirections();
		return;
	}
	if (!Target)
	{
		ResetAvailableStrafeDirections();
		return;
	}
	if (CurrentStrafeTime >= MaxStrafeTime)
	{
		ResetAvailableStrafeDirections();
		return;
	}
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
	FRotator InterpolatedRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, 0.01f, 1);
	SetActorRotation(InterpolatedRotation);
	FVector StrafeDirectionVector;
	// gengine print strafe direction
	
	switch (CurrentStrafeDirection)
	{
		case EStrafingMovementDirection::ESMD_Left:
			StrafeDirectionVector = FGeneralUtils::ClampVector(GetActorRightVector() * -1, -0.3f, 0.3f);
			AddMovementInput(StrafeDirectionVector);
			break;
		case EStrafingMovementDirection::ESMD_Right:
			StrafeDirectionVector = FGeneralUtils::ClampVector(GetActorRightVector(), -0.3f, 0.3f);
			AddMovementInput(StrafeDirectionVector);
			break;
		case EStrafingMovementDirection::ESMD_Backward:
			StrafeDirectionVector = FGeneralUtils::ClampVector(GetActorForwardVector() * -1, -0.3f, 0.3f);
			AddMovementInput(StrafeDirectionVector);
			break;
		break;
	}
	float AmountToAdd = FMath::RandRange(0.005f, 0.01f) + (CurrentStrafeDirection == EStrafingMovementDirection::ESMD_Backward) ? 0.005f : 0.f;
	GetBlackboardComponent()->SetValueAsFloat("StrafeTime", CurrentStrafeTime + AmountToAdd);
	GetWorld()->GetTimerManager().SetTimer(StrafeTimer, this, &AVorpisBaseNpc::Strafe, StrafeTime, false);
}

ECharacterPersonality AVorpisBaseNpc::InterfaceGetPersonality()
{
	return CharacterStateComponent->GetCharacterPersonality();
}
AActor* AVorpisBaseNpc::GetSplinePathAsActor(){	return SplinePathActor; }

bool AVorpisBaseNpc::RecieveAttack(FFinishedAttackStruct AttackData)
{
	ECombatPosition CharacterPosition = CombatComponent->GetCombatPosition();
	ECombatPosition AdjustedEnemyPosition = AdjustCombatPosition(AttackData.AttackData.InitialAttackData.Position);
	// instead of false, we need to  see if they have a weapon or shield to block with
	if (AdjustedEnemyPosition == CharacterPosition) {
		// is parrying?
			// get parry reaction
		// chamber, in place dodge, ect?
		if (CharacterStateComponent->GetCharacterCombatState() == ECombatState::ECS_Dodging) {
			return false;
		}
		UAnimMontage* BlockMontage = MontageManagerComponent->GetBlockReactionMontage(CharacterPosition, false);
		if (BlockMontage) {
			PlayAnimMontage(BlockMontage);
		}
	}
	else {
		UAnimMontage* HitMontage = MontageManagerComponent->GetHitReactionMontage(AttackData.AttackData.InitialAttackData.Position);
		GetBlackboardComponent()->SetValueAsEnum("CombatState", (uint8)EAiCombatState::EACS_HitStunned);
		if (HitMontage) {
			PlayAnimMontage(HitMontage);
			ABaseRpgCharacter::SpawnBloodAtLocation(AttackData.HitTraceResults.HitLocation);
		}
	}
	return true;
}

void AVorpisBaseNpc::RecieveAttackSignal()
{
	// if something something, we need some kind of tracking
	float RaondomFloat = FMath::FRandRange(0.f, 1.f);
	if (RaondomFloat > 0.65)
	{
		DodgeInDirection(EDodgeDirection::ESMD_Backward);
	}
}


// enum to string
// enumtostring
// FString Strafe = *UEnum::GetValueAsName(CurrentStrafeDirection).ToString();