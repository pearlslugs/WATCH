// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ItemData/ItemStructs.h"
#include "VorpisSaveGameObject.generated.h"

/**
 * 
 */
UCLASS()
class VORPISGAMEMANAGEMENTMODULE_API UVorpisSaveGameObject : public USaveGame
{
	GENERATED_BODY()

public:

	//_______________________________________________________________________________________________

	//_______________________________________________________________________________________________
	// item data

	// 
	// pick ups will be around the map, when they are picked up
	// they should be removed from here
	// this should be used to get a map of items and spawn them in the chosen location
	// when you drop an item, add it to this list
	
	//_______________________________________________________________________________________________
	// next data  \ 

	// equipment save objects
		
	UPROPERTY()
	TMap<EEquipmentSlot, FItemData> PlayerEquipment;
	UPROPERTY()
	TMap<int, FItemData> PlayerQuickslots;
	UPROPERTY()
	FItemData RightHandItem;
	UPROPERTY()
	FItemData LeftHandItem;
		// save
	UFUNCTION()
	void SavePlayerEquipment(TMap<EEquipmentSlot, FItemData> NewPlayerEquipment);
	UFUNCTION()
	void SavePlayerQuickslots(TMap<int, FItemData> NewQuickslots);
	UFUNCTION()
	void SaveRightHandItem(FItemData Item);
	UFUNCTION()
	void SaveLeftHandItem(FItemData Item);
		// load
	UFUNCTION()
	TMap<EEquipmentSlot, FItemData> LoadPlayerEquipment();
	TMap<int, FItemData> LoadPlayerQuickslots();
	FItemData LoadRightHandItem();
	FItemData LoadLeftHandItem();

		// delete

		// put

	// item save data
	UPROPERTY()
	TMap<FGuid, FPickUpData> AllPickUps;
		// save
	UFUNCTION()
	void SaveNewPickUp(FPickUpData ItemToSave);
		// load
	UFUNCTION()
	TMap<FGuid, FPickUpData> LoadAllPickups();
	UFUNCTION()
	FPickUpData LoadSinglePickup(FGuid PickupGuid);
		//delete
	UFUNCTION()
	void DeleteSinglePickUp(FGuid PickUpGuid);
		// put
	UFUNCTION()
	void PutSinglePickUp(FPickUpData ItemToPut);
};
