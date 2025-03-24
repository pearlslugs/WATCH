// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInterfaces/EquipmentComponentInterface.h"

// Add default functionality here for any IEquipmentComponentInterface functions that are not pure virtual.
void IEquipmentComponentInterface::InterfaceEquipItem(FItemData ItemData, EEquipmentSlot Slot)
{
	//
}


FItemData IEquipmentComponentInterface::InterfaceGetEquippedItem(EEquipmentSlot Slot)
{
	return FItemData();
}
bool IEquipmentComponentInterface::InterfaceGetIsSlotEmpty(EEquipmentSlot Slot)
{
	return false;
}
FItemData IEquipmentComponentInterface::InterfaceUnequipItem(EEquipmentSlot Slot)
{
	return FItemData();
}
FItemData IEquipmentComponentInterface::InterfaceSwapItem(EEquipmentSlot Slot, FItemData ItemToUse)
{
	return FItemData();
}

void IEquipmentComponentInterface::InterfaceAddItemToQuickslots(FItemData ItemData, int Slot)
{
	//
}
int IEquipmentComponentInterface::InterfaceGetFirstEmptyQuickslot()
{
	return -1;
}
FItemData IEquipmentComponentInterface::InterfaceGetQuickslot(int Slot)
{
	return FItemData();
}
FItemData IEquipmentComponentInterface::InterfaceRemoveQuickslot(int Slot)
{
	return FItemData();

}
FItemData IEquipmentComponentInterface::InterfaceSwapQuickslot(int slot, FItemData ItemToUse)
{
	return FItemData();
}
bool IEquipmentComponentInterface::InterfaceGetIsQuickslotEmpty(int Slot)
{
	return false;
}