// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData/ItemStructs.h"
#include "Slot/SingleUserWidgetInventoryslot.h"
#include "QuickslotsUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class VORPISEQUIPMENTMODULE_API UQuickslotsUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	UActorComponent* EquipmentComponent;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	int MaxQuickslots = 6;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	TArray<USingleUserWidgetInventoryslot*> Quickslots;


	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool UpdateSlot(FItemData NewItem, int QuickslotIndex);
	
};
