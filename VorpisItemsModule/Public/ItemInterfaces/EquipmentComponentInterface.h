// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemData/ItemStructs.h"
#include "EquipmentComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEquipmentComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VORPISITEMSMODULE_API IEquipmentComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void InterfaceEquipItem(FItemData ItemData, EEquipmentSlot Slot);
	virtual FItemData InterfaceGetEquippedItem(EEquipmentSlot Slot);
	virtual bool InterfaceGetIsSlotEmpty(EEquipmentSlot Slot);
	virtual FItemData InterfaceUnequipItem(EEquipmentSlot Slot);
	virtual FItemData InterfaceSwapItem(EEquipmentSlot Slot, FItemData ItemToUse);

	// quickslots
	virtual void InterfaceAddItemToQuickslots(FItemData ItemData, int Slot);
	virtual int InterfaceGetFirstEmptyQuickslot();
	virtual FItemData InterfaceGetQuickslot(int Slot);
	virtual FItemData InterfaceRemoveQuickslot(int Slot);
	virtual FItemData InterfaceSwapQuickslot(int slot, FItemData ItemToUse);
	virtual bool InterfaceGetIsQuickslotEmpty(int Slot);
};
