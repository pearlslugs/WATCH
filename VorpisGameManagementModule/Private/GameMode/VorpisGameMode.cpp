// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/VorpisGameMode.h"
#include "Kismet/GameplayStatics.h"

void AVorpisGameMode::MakeNewSaveSlot(FString NewSlotName)
{
	VorpisSaveGameObject = nullptr;
	SlotName = NewSlotName;
	AVorpisGameMode::CreateSaveObject();
}

void AVorpisGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (!SlotName.IsEmpty()) {
		AVorpisGameMode::LoadGame();
	} else {
		// if this fails, there is an error in your configuration
		UE_LOG(LogTemp, Error, TEXT("SlotName is empty!"));
	}
}

void AVorpisGameMode::BeginDestroy()
{
	Super::BeginDestroy();
}

void AVorpisGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	AVorpisGameMode::SaveGameToSlot();
}

void AVorpisGameMode::CreateSaveObject()
{
	VorpisSaveGameObject = Cast<UVorpisSaveGameObject>(UGameplayStatics::CreateSaveGameObject(UVorpisSaveGameObject::StaticClass()));
}

void AVorpisGameMode::SaveGameToSlot()
{
	if (VorpisSaveGameObject) {
		UGameplayStatics::AsyncSaveGameToSlot(VorpisSaveGameObject, SlotName, 0);
	} else {
		AVorpisGameMode::LoadGame();
	}
}

void AVorpisGameMode::LoadGame()
{
	VorpisSaveGameObject = Cast<UVorpisSaveGameObject>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (!VorpisSaveGameObject) {
		AVorpisGameMode::CreateSaveObject();
	}
}

// in this funciton, we see how we use the save and load systme.
// this is to catch any nullptr to the save object, if it is null, 
// we load game so initialize it, then run the function again.

void AVorpisGameMode::SaveNewPickUp(FPickUpData ItemToSave)
{
	if (VorpisSaveGameObject) {
		VorpisSaveGameObject->SaveNewPickUp(ItemToSave);
	} else {
		AVorpisGameMode::LoadGame();
		AVorpisGameMode::SaveNewPickUp(ItemToSave);
	}
}
TMap<FGuid, FPickUpData> AVorpisGameMode::LoadAllPickups()
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->LoadAllPickups();
	} else {
		AVorpisGameMode::LoadGame();
		return AVorpisGameMode::LoadAllPickups();
	}
}

TMap<int, FItemData> AVorpisGameMode::LoadQuickslots()
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->LoadPlayerQuickslots();
	}
	else {
		AVorpisGameMode::LoadGame();
		return VorpisSaveGameObject->LoadPlayerQuickslots();
	}
}

TMap<int, FItemData> AVorpisGameMode::InterfaceLoadQuickslots_Implementation()
{
	TMap<int, FItemData> Blank;
	return Blank;
}

void AVorpisGameMode::SaveQuickslots(const TMap<int, FItemData>& PlayerEquipment)
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->SavePlayerQuickslots(PlayerEquipment);
	}
	else {
		AVorpisGameMode::LoadGame();
		return VorpisSaveGameObject->SavePlayerQuickslots(PlayerEquipment);
	}
}

void AVorpisGameMode::InterfaceSavePlayerEquipment_Implementation(const TMap<EEquipmentSlot, FItemData>& NewPlayerEquipment)
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->SavePlayerEquipment(NewPlayerEquipment);
	}
	else {
		AVorpisGameMode::LoadGame();
		return VorpisSaveGameObject->SavePlayerEquipment(NewPlayerEquipment);
	}
}

void AVorpisGameMode::InterfaceSaveQuickslots_Implementation(const TMap<int, FItemData>& PlayerQuickslots){}
void AVorpisGameMode::InterfaceSaveRightHandItem_Implementation(const FItemData& Item){}
void AVorpisGameMode::SaveRightHandItem(const FItemData& Item)
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->SaveRightHandItem(Item);
	}
	else {
		AVorpisGameMode::LoadGame();
		return VorpisSaveGameObject->SaveRightHandItem(Item);
	}
}
void AVorpisGameMode::InterfaceSaveLeftHandItem_Implementation(const FItemData& Item) {}
void AVorpisGameMode::SaveLeftHandItem(const FItemData& Item)
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->SaveLeftHandItem(Item);
	}
	else {
		AVorpisGameMode::LoadGame();
		return VorpisSaveGameObject->SaveLeftHandItem(Item);
	}
}

FItemData AVorpisGameMode::InterfaceLoadRightHandItem_Implementation(){return FItemData();}
FItemData AVorpisGameMode::LoadRightHandItem()
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->LoadRightHandItem();
	}
	else {
		AVorpisGameMode::LoadGame();
		return VorpisSaveGameObject->LoadRightHandItem();
	}
}
FItemData AVorpisGameMode::InterfaceLoadLeftHandItem_Implementation(){return FItemData();}
FItemData AVorpisGameMode::LoadLeftHandItem()
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->LoadLeftHandItem();
	}
	else {
		AVorpisGameMode::LoadGame();
		return VorpisSaveGameObject->LoadLeftHandItem();
	}
}


FPickUpData AVorpisGameMode::InterfaceLoadSinglePickup_Implementation(FGuid PickupGuid){return FPickUpData();}
FPickUpData AVorpisGameMode::LoadSinglePickup(FGuid PickupGuid)
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->LoadSinglePickup(PickupGuid);
	}
	else {
		AVorpisGameMode::LoadGame();
		return VorpisSaveGameObject->LoadSinglePickup(PickupGuid);
	}
}
void AVorpisGameMode::InterfaceDeleteSinglePickUp_Implementation(FGuid PickUpGuid) {};
void AVorpisGameMode::DeleteSinglePickUp(FGuid PickUpGuid)
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->DeleteSinglePickUp(PickUpGuid);
	}
	else {
		AVorpisGameMode::LoadGame();
		return VorpisSaveGameObject->DeleteSinglePickUp(PickUpGuid);
	}
}
void AVorpisGameMode::InterfacePutSinglePickUp_Implementation(FPickUpData ItemToPut) {};
void AVorpisGameMode::PutSinglePickUp(FPickUpData ItemToPut)
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->PutSinglePickUp(ItemToPut);
	}
	else {
		AVorpisGameMode::LoadGame();
		return VorpisSaveGameObject->PutSinglePickUp(ItemToPut);
	}
}

TMap<FGuid, FPickUpData> AVorpisGameMode::InterfaceLoadAllPickups_Implementation()
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->LoadAllPickups();
	}
	else {
		AVorpisGameMode::LoadGame();
		return VorpisSaveGameObject->LoadAllPickups();
	}
}

TMap<EEquipmentSlot, FItemData> AVorpisGameMode::InterfaceLoadPlayerEquipment_Implementation()
{
	TMap<EEquipmentSlot, FItemData> Blank;
	return Blank;
}

TMap<EEquipmentSlot, FItemData> AVorpisGameMode::LoadPlayerEquipment()
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->LoadPlayerEquipment();
	}
	else {
		AVorpisGameMode::LoadGame();
		return VorpisSaveGameObject->LoadPlayerEquipment();
	}
}

void AVorpisGameMode::SavePlayerEquipment(const TMap<EEquipmentSlot, FItemData>& NewPlayerEquipment)
{
	if (VorpisSaveGameObject) {
		return VorpisSaveGameObject->SavePlayerEquipment(NewPlayerEquipment);
	}
	else {
		AVorpisGameMode::LoadGame();
		return VorpisSaveGameObject->SavePlayerEquipment(NewPlayerEquipment);
	}
}