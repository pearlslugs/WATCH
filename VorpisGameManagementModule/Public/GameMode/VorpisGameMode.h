// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SaveGameObject/VorpisSaveGameObject.h"
#include "GameMode/GameModeInterface/GameModeInterface.h"
#include "ItemData/ItemStructs.h"
#include "VorpisGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VORPISGAMEMANAGEMENTMODULE_API AVorpisGameMode : public AGameModeBase, public IGameModeInterface
{
	GENERATED_BODY()
public:

protected:

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	// save game

	UFUNCTION()
	void LoadGame();
	UFUNCTION(BlueprintCallable)
	void SaveGameToSlot();
	UFUNCTION()
	void CreateSaveObject();
	UPROPERTY()
	FString SlotName = "CHARACTER_Doug";
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SetSelectedGameSlotName(FString NewSelectedGameSlotName) { SlotName = NewSelectedGameSlotName; };
	UFUNCTION(BlueprintPure, Category = "SaveGame")
	FString GetSelectedGameSlotName() { return SlotName; };
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SetSaveGameObject(UVorpisSaveGameObject* NewSaveGameObject) { VorpisSaveGameObject = NewSaveGameObject; };
	UFUNCTION(BlueprintCallable)
	void MakeNewSaveSlot(FString NewSlotName);


	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UVorpisSaveGameObject* VorpisSaveGameObject;



	//_______________________________________________________________________________________________
	// item data
	UFUNCTION(BlueprintCallable)
	void SaveNewPickUp(FPickUpData ItemToSave);
	UFUNCTION(BlueprintCallable)
	TMap<FGuid, FPickUpData> LoadAllPickups();
	UFUNCTION(BlueprintCallable)
	void SaveQuickslots(const TMap<int, FItemData>& PlayerQuickslots);
	UFUNCTION(BlueprintCallable)
	TMap<int, FItemData> LoadQuickslots();

	// player equipment
	//_______________________________________________________________________________________________

	// equipment 
	virtual void InterfaceSavePlayerEquipment_Implementation(const TMap<EEquipmentSlot, FItemData>& NewPlayerEquipment) override;
	UFUNCTION(BlueprintCallable)
	void SavePlayerEquipment(const TMap<EEquipmentSlot, FItemData>& NewPlayerEquipment);
	virtual TMap<EEquipmentSlot, FItemData> InterfaceLoadPlayerEquipment_Implementation() override;
	UFUNCTION(BlueprintCallable)
	TMap<EEquipmentSlot, FItemData> LoadPlayerEquipment();
	
	// quick slots
	virtual void InterfaceSaveQuickslots_Implementation(const TMap<int, FItemData>& PlayerEquipment) override;
	virtual TMap<int, FItemData> InterfaceLoadQuickslots_Implementation() override;

	// held weapons
	virtual void InterfaceSaveRightHandItem_Implementation(const FItemData& Item) override;
	UFUNCTION(BlueprintCallable)
	void SaveRightHandItem(const FItemData& Item);
	virtual void InterfaceSaveLeftHandItem_Implementation(const FItemData& Item) override;
	UFUNCTION(BlueprintCallable)
	void SaveLeftHandItem(const FItemData& Item);

	virtual FItemData InterfaceLoadRightHandItem_Implementation() override;
	UFUNCTION(BlueprintCallable)
	FItemData LoadRightHandItem();
	virtual FItemData InterfaceLoadLeftHandItem_Implementation() override;
	UFUNCTION(BlueprintCallable)
	FItemData LoadLeftHandItem();


	// pickups
	//_______________________________________________________________________________________________

	// load
	virtual FPickUpData InterfaceLoadSinglePickup_Implementation(FGuid PickupGuid) override;
	UFUNCTION(BlueprintCallable)
	FPickUpData LoadSinglePickup(FGuid PickupGuid);
	virtual TMap<FGuid, FPickUpData> InterfaceLoadAllPickups_Implementation() override;
	
	// save
	virtual void InterfaceSaveNewPickUp_Implementation(const FPickUpData& NewPickUp) override {};
	// delete
	void InterfaceDeleteSinglePickUp_Implementation(FGuid PickUpGuid);
	UFUNCTION(BlueprintCallable)
	void DeleteSinglePickUp(FGuid PickUpGuid);
	// put
	void InterfacePutSinglePickUp_Implementation(FPickUpData ItemToPut);
	UFUNCTION(BlueprintCallable)
	void PutSinglePickUp(FPickUpData ItemToPut);
};
