// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameObject/VorpisSaveGameObject.h"

void UVorpisSaveGameObject::SaveNewPickUp(FPickUpData ItemToSave)
{
	AllPickUps.Add(ItemToSave.ItemData.ItemGuid, ItemToSave);
}

TMap<FGuid, FPickUpData> UVorpisSaveGameObject::LoadAllPickups()
{
	return AllPickUps;
}