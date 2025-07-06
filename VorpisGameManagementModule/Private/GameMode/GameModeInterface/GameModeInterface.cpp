// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GameModeInterface/GameModeInterface.h"

// Add default functionality here for any IGameModeInterface functions that are not pure virtual.


TMap<FGuid, FPickUpData> IGameModeInterface::InterfaceLoadAllPickups_Implementation()
{
	TMap<FGuid, FPickUpData> CurrentPickUpData;
	return CurrentPickUpData;
}

TMap<int, FItemData> IGameModeInterface::InterfaceLoadQuickslots_Implementation()
{
	TMap<int, FItemData> Blank;
	return Blank;
}

TMap<EEquipmentSlot, FItemData> IGameModeInterface::InterfaceLoadPlayerEquipment_Implementation()
{
	TMap<EEquipmentSlot, FItemData> Blank;
	return Blank;
}