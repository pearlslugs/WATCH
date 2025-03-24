// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterStateData/CharacterStateEnums.h"
#include "CombatData/CombatStructs.h"
#include "VorpisPlayerCharacterInterface.generated.h"

class UDialogueDataAsset;
class UUserWidget;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UVorpisPlayerCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VORPISCHARACTERINTERFACEMODULE_API IVorpisPlayerCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CloseInputBuffer();
	virtual void CloseInputBuffer_Implementation();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OpenInputBuffer();
	virtual void OpenInputBuffer_Implementation();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ToggleSelectedEquipmentEquipped(bool State);
	virtual void ToggleSelectedEquipmentEquipped_Implementation(bool State);

	virtual void ControllerInputDown() {};
	virtual void ControllerInputUp() {};
	virtual void ControllerInputLeft() {};
	virtual void ControllerInputRight() {};
	virtual void ControllerInputSelect() {};
	virtual void ControllerInputBack() {};
	virtual void ControllerInputStart() {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MountDialogueComponentAndSetAsset(UDialogueDataAsset* AssetToMount, UUserWidget* Widget);
	virtual void MountDialogueComponentAndSetAsset_Implementation(UDialogueDataAsset* AssetToMount, UUserWidget* Widget) {};

};
