// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GameModeInterface/GameModeInterface.h"

// Add default functionality here for any IGameModeInterface functions that are not pure virtual.


void IGameModeInterface::InterfaceSaveNewPickUp(FPickUpData ItemToSave)
{
	//
}
TMap<FGuid, FPickUpData> IGameModeInterface::InterfaceLoadAllPickups()
{
	TMap<FGuid, FPickUpData> CurrentPickUpData;
	return CurrentPickUpData;
}
