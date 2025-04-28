// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterStateData/CharacterStateEnums.h"
#include "NpcInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNpcInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VORPISCHARACTERINTERFACEMODULE_API INpcInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual AActor* GetSplinePathAsActor();

	virtual ECharacterPersonality InterfaceGetPersonality() { return ECharacterPersonality::ECP_None; };

	virtual void CreateDialogueWidget() {};

	virtual void InterfaceAttack() {};

	virtual void StartStrafing() {};
	virtual void StopStrafing() {};

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Npc Interface")
	bool IsNpc();
	virtual bool IsNpc_Implementation() { return false; };

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ToggleSelectedEquipmentEquipped(bool State);
	virtual void ToggleSelectedEquipmentEquipped_Implementation(bool State) {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InterfaceClearAttacking();
	virtual void InterfaceClearAttacking_Implementation() {};

};
