// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemData/ItemEnums.h"
#include "ItemData/ItemStructs.h"
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
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool CheckToolProperties(const TMap<EToolProperties, int32>& RequiredTools);
	virtual bool CheckToolProperties_Implementation(const TMap<EToolProperties, int32>& RequiredTools) { return false; };
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

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StartHarvestingFuelPlant(AActor* PlantActor);
	virtual void StartHarvestingFuelPlant_Implementation(AActor* PlantActor) {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void GetPickUp(AActor* PickUpActor);
	virtual void GetPickUp_Implementation(AActor* PickUpActor) {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void FinishPickingUpItem(bool RightHand);
	virtual void FinishPickingUpItem_Implementation(bool RightHand) {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TArray<FItemData> GetEquippedItems();
	virtual TArray<FItemData> GetEquippedItems_Implementation();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DropItem(bool RightHand);
	virtual void DropItem_Implementation(bool RightHand) {};
};
