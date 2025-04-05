// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterStateData/CharacterStateEnums.h"
#include "CombatData/CombatStructs.h"
#include "BaseRpgCharacterInterface.generated.h"



// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBaseRpgCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VORPISCHARACTERINTERFACEMODULE_API IBaseRpgCharacterInterface
{
	GENERATED_BODY()
public:
	virtual USkinnedMeshComponent* GetSkinnedMesh();
	virtual bool IsDead();
	virtual bool RecieveAttack(FFinishedAttackStruct AttackData) { return false; };
	virtual void RecieveAttackSignal() {};

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InterfacePopulateInitialAttackData(FInitialAttackData InitialAttackData);
	virtual void InterfacePopulateInitialAttackData_Implementation(FInitialAttackData InitialAttackData);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InterfaceToggleWeaponCollision(bool State);
	virtual void InterfaceToggleWeaponCollision_Implementation(bool State);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RotateTowardsTarget(bool State);
	virtual void RotateTowardsTarget_Implementation(bool State);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InterfaceSetCharacterGeneralState(EGeneralState NewState);
	virtual void InterfaceSetCharacterGeneralState_Implementation(EGeneralState NewState);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InterfaceSetCombatPosition(ECombatPosition NewPosition);
	virtual void InterfaceSetCombatPosition_Implementation(ECombatPosition NewPosition) {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InterfaceSetCharacterCombatState(ECombatState NewState);
	virtual void InterfaceSetCharacterCombatState_Implementation(ECombatState NewState);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RecieveEnemyCombatPosition(ECombatPosition EnemyPosition);
	virtual void RecieveEnemyCombatPosition_Implementation(ECombatPosition EnemyPosition) {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool BreakHitStun();
	virtual bool BreakHitStun_Implementation() { return false; };
};
