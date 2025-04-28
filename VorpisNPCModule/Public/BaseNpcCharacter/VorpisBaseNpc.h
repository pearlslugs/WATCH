// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RpgCharacter/BaseRpgCharacter.h"
#include "Npc/NpcInterface.h"
#include "DialogueData/DialogueData.h"
#include "CharacterStateData/CharacterStateEnums.h"
#include "NpcDialogue/NpcDialogueComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "GeneralData/GeneralData.h"
#include "VorpisBaseNpc.generated.h"

/**
 * 
 */

class AAiController;
class UBlackboardComponent;

UCLASS()
class VORPISNPCMODULE_API AVorpisBaseNpc : public ABaseRpgCharacter, public INpcInterface
{
	GENERATED_BODY()

public:
	AVorpisBaseNpc();
	// ai timers
	FTimerHandle ResetAttackCoooldownTimer;
	float ResetAttackCooldownTime = 3.0f;
	FTimerDynamicDelegate ResetAttackCooldownDelegate;

	FTimerHandle ClearAttackStartedTimer;
	float ClearAttackStartedTime = 0.7f;
	FTimerDynamicDelegate ClearAttackStartedDelagate;

	FTimerHandle CallAttackTimer;
	float CallAttackTime = 0.01f;
	FTimerDynamicDelegate CallAttackDelagate;
	UFUNCTION()
	void StartAttackCoolDown();
	UFUNCTION()
	void ResetAttackCooldown();
	FTimerHandle StrafeTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Npc")
	AActor* SplinePathActor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;
	UFUNCTION()
	UBlackboardComponent* GetBlackboardComponent();

	UFUNCTION(BlueprintCallable, Category = "Perception")
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	// combat 
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Attack();
	UPROPERTY()
	bool AttackStarted;
	UFUNCTION(BlueprintCallable)
	void ClearAttackStarted() { AttackStarted = false; };


protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	AAIController* AIController;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	AActor* TargetActor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	UNpcDialogueComponent* NpcDialogueComponent;


	UFUNCTION(BlueprintCallable)
	void FinishDialogue(EDialogueOutcome Outcome);

	// strafing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	EStrafingMovementDirection CurrentStrafeDirection;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TArray<EStrafingMovementDirection> AllStrafeDirections;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TArray<EStrafingMovementDirection> AvailableStrafeDirections;
	UFUNCTION()
	void ResetAvailableStrafeDirections();
	UFUNCTION()
	void RandomlyAssignStrafeDirection();
	float StrafeTime = 0.01f;

	UFUNCTION(BlueprintCallable)
	void SyncStateWithBehaviorTree();
	FTimerHandle SyncStateTimer;
	float SyncStateTime = 1.0f;
	UFUNCTION()
	ECombatState GetCombatState() { return CharacterStateComponent->GetCharacterCombatState(); };


	UFUNCTION()
	void Strafe();
private:

public:

	//// implementable interfaces
	virtual void InterfaceSetCharacterGeneralState_Implementation(EGeneralState NewState) override {};
	virtual void InterfaceSetCharacterCombatState_Implementation(ECombatState NewCombatState) override {};
	virtual void InterfaceToggleWeaponCollision_Implementation(bool State) override {};
	virtual void RotateTowardsTarget_Implementation(bool State) override {};
	virtual void InterfacePopulateInitialAttackData_Implementation(FInitialAttackData InitialAttackData) override {};

	// interfaces
	virtual AActor* GetSplinePathAsActor() override;
	virtual ECharacterPersonality InterfaceGetPersonality() override;
	virtual void RecieveAttackSignal() override;
	virtual void CreateDialogueWidget() override;
	virtual void InterfaceAttack() override;
	virtual bool IsNpc_Implementation() override { return true; };
	virtual void ToggleSelectedEquipmentEquipped_Implementation(bool State) {};
	virtual void StartStrafing();
	virtual void StopStrafing();
	virtual bool RecieveAttack(FFinishedAttackStruct AttackData) override;
	virtual void InterfaceClearAttacking_Implementation() override {};
};