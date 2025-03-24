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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	
	// interfaces
	virtual void InterfaceSaveNewPickUp(FPickUpData ItemToSave) { SaveNewPickUp(ItemToSave); };
	virtual TMap<FGuid, FPickUpData> InterfaceLoadAllPickups() { return LoadAllPickups(); };





	// save game

	UFUNCTION()
	void LoadGame();
	UFUNCTION(BlueprintCallable)
	void SaveGameToSlot();
	UFUNCTION()
	void CreateSaveObject();
	FString SlotName = "CHARACTER_Doug";
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SetSelectedGameSlotName(FString NewSelectedGameSlotName) { SlotName = NewSelectedGameSlotName; };
	UFUNCTION(BlueprintPure, Category = "SaveGame")
	FString GetSelectedGameSlotName() { return SlotName; };
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SetSaveGameObject(UVorpisSaveGameObject* NewSaveGameObject) { VorpisSaveGameObject = NewSaveGameObject; };
	UFUNCTION(BlueprintCallable)
	void MakeNewSaveSlot(FString NewSlotName);


	UPROPERTY()
	UVorpisSaveGameObject* VorpisSaveGameObject;



	//_______________________________________________________________________________________________
	// item data
	UFUNCTION()
	void SaveNewPickUp(FPickUpData ItemToSave);
	UFUNCTION()
	TMap<FGuid, FPickUpData> LoadAllPickups();

	//_______________________________________________________________________________________________
	
};
