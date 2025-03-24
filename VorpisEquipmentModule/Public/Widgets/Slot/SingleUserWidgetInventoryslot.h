// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData/ItemStructs.h"
#include "SingleUserWidgetInventoryslot.generated.h"

/**
 * 
 */
UCLASS()
class VORPISEQUIPMENTMODULE_API USingleUserWidgetInventoryslot : public UUserWidget
{
	GENERATED_BODY()
public:
	// you need to override this in blueprint to use the widgets you add there
	UFUNCTION(BlueprintNativeEvent, Category = "Update")
	bool UpdateSlotEvent(FItemData NewItem);
	virtual bool UpdateSlotEvent_Implementation(FItemData NewItem);
};
