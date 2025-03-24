// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveGameObject/VorpisSaveGameObject.h"
#include "VorpisGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VORPISGAMEMANAGEMENTMODULE_API UVorpisGameInstance : public UGameInstance
{
	GENERATED_BODY()
public: 

	UVorpisGameInstance();

	// slot name 
	// this works with the game instance to get all save games in the save folder
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveGame", meta = (AllowPrivateAccess = "true"))
	FString SelectedGameSlotName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FString> SaveGameSlotNames;
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	TArray<FString> GetSaveGameSlotNames() { return SaveGameSlotNames; };
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void FindSaveGameSlotNames();
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SetSelectedGameSlotName(FString NewSelectedGameSlotName) { SelectedGameSlotName = NewSelectedGameSlotName; };
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	FString GetSelectedGameSlotName() { return SelectedGameSlotName; };

	// save object
	UPROPERTY()
	UVorpisSaveGameObject* SaveGameObject;
	
};
