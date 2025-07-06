// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameObject/VorpisSaveGameObject.h"

// player items
void UVorpisSaveGameObject::SavePlayerEquipment(TMap<EEquipmentSlot, FItemData> NewPlayerEquipment)
{
	PlayerEquipment = NewPlayerEquipment;
}
TMap<EEquipmentSlot, FItemData> UVorpisSaveGameObject::LoadPlayerEquipment()
{
	if (PlayerEquipment.Num() > 0) {
		return PlayerEquipment;
	}
	TMap<EEquipmentSlot, FItemData> Blank;
	return Blank;
}

void UVorpisSaveGameObject::SavePlayerQuickslots(TMap<int, FItemData> NewQuickslots)
{
	PlayerQuickslots.Empty();
	PlayerQuickslots = NewQuickslots;
}
TMap<int, FItemData> UVorpisSaveGameObject::LoadPlayerQuickslots()
{
	if (PlayerQuickslots.Num() > 0) {
		return PlayerQuickslots;
	}
	TMap<int, FItemData> Blank;
	return Blank;
}

void UVorpisSaveGameObject::SaveRightHandItem(FItemData Item)
{
	RightHandItem = Item;
}
void UVorpisSaveGameObject::SaveLeftHandItem(FItemData Item)
{
	LeftHandItem = Item;
}

FItemData UVorpisSaveGameObject::LoadRightHandItem()
{
	return RightHandItem;
}
FItemData UVorpisSaveGameObject::LoadLeftHandItem()
{
	return LeftHandItem;
}


// pick ups

void UVorpisSaveGameObject::SaveNewPickUp(FPickUpData ItemToSave)
{
	AllPickUps.Add(ItemToSave.ItemData.ItemGuid, ItemToSave);
}

void UVorpisSaveGameObject::DeleteSinglePickUp(FGuid PickUpGuid)
{
	if (!AllPickUps.Contains(PickUpGuid)) {
		return;
	}
	FPickUpData FoundItem = AllPickUps.FindRef(PickUpGuid);
	// Items that were dropped are dynamic and not placed in to the editor. these will only exist if they are in  the map and spawned from data.
	// items that are not dropped in to world are placed by me, they need to be set to not active so that they will delete themselves at begin play
	if (!FoundItem.DroppedInToWorld) {
		FoundItem.Active = false;
		AllPickUps.Emplace(PickUpGuid, FoundItem);
	}
	else {
		AllPickUps.Remove(PickUpGuid);
	}
}
void UVorpisSaveGameObject::PutSinglePickUp(FPickUpData ItemToPut)
{
	FGuid ItemGuid = ItemToPut.ItemData.ItemGuid;
	AllPickUps.Emplace(ItemGuid, ItemToPut);
}

TMap<FGuid, FPickUpData> UVorpisSaveGameObject::LoadAllPickups()
{
	if (AllPickUps.Num() > 0) {
		return AllPickUps;
	}
	TMap<FGuid, FPickUpData> Blank;
	return Blank;
}

FPickUpData UVorpisSaveGameObject::LoadSinglePickup(FGuid PickupGuid)
{
	if (AllPickUps.Contains(PickupGuid))
	{
		return AllPickUps.FindRef(PickupGuid);
	}
	return FPickUpData();
}