// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemData/ItemStructs.h"
#include "ItemData/ItemEnums.h"
#include "GameModeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VORPISGAMEMANAGEMENTMODULE_API IGameModeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// pick ups
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InterfaceSaveNewPickUp(const FPickUpData& NewPickUp);
	virtual void InterfaceSaveNewPickUp_Implementation(const FPickUpData& NewPickUp) {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	TMap<FGuid, FPickUpData> InterfaceLoadAllPickups();
	virtual TMap<FGuid, FPickUpData> InterfaceLoadAllPickups_Implementation();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	FPickUpData InterfaceLoadSinglePickup(FGuid PickupGuid);
	virtual FPickUpData InterfaceLoadSinglePickup_Implementation(FGuid PickupGuid) { return FPickUpData(); };
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InterfaceDeleteSinglePickUp(FGuid PickUpGuid);
	void InterfaceDeleteSinglePickUp_Implementation(FGuid PickUpGuid) {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InterfacePutSinglePickUp(FPickUpData ItemToPut);
	void InterfacePutSinglePickUp_Implementation(FPickUpData ItemToPut) {};

	// player equipment
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InterfaceSavePlayerEquipment(const TMap<EEquipmentSlot, FItemData>& NewPlayerEquipment);
	virtual void InterfaceSavePlayerEquipment_Implementation(const TMap<EEquipmentSlot, FItemData>& NewPlayerEquipment) {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InterfaceSaveQuickslots(const TMap<int, FItemData>& PlayerQuickslots);
	virtual void InterfaceSaveQuickslots_Implementation(const TMap<int, FItemData>& PlayerQuickslots) {};

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	TMap<int, FItemData> InterfaceLoadQuickslots();
	virtual TMap<int, FItemData> InterfaceLoadQuickslots_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	TMap<EEquipmentSlot, FItemData> InterfaceLoadPlayerEquipment();
	virtual TMap<EEquipmentSlot, FItemData> InterfaceLoadPlayerEquipment_Implementation();
	// held items

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	FItemData InterfaceLoadRightHandItem();
	virtual FItemData InterfaceLoadRightHandItem_Implementation() { return FItemData(); };
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	FItemData InterfaceLoadLeftHandItem();
	virtual FItemData InterfaceLoadLeftHandItem_Implementation() { return FItemData(); };
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InterfaceSaveRightHandItem(const FItemData& Item);
	virtual void InterfaceSaveRightHandItem_Implementation(const FItemData& Item) {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void InterfaceSaveLeftHandItem(const FItemData& Item);
	virtual void InterfaceSaveLeftHandItem_Implementation(const FItemData& Item) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Base function call, no override");
		}
	};

	
};
