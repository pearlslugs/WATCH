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