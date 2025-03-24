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
	float ResetAttackCooldownTime = 5.0f;
	FTimerDynamicDelegate ResetAttackCooldownDelegate;
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
	void Attack();


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
	virtual void CreateDialogueWidget() override;
	virtual void InterfaceAttack() override;
	virtual bool IsNpc_Implementation() override { return true; };
	virtual void ToggleSelectedEquipmentEquipped_Implementation(bool State) {};
	virtual void InterfaceSetCombatState_Implementation(uint8 state) {};
	virtual void StartStrafing();
	virtual void StopStrafing();
};
