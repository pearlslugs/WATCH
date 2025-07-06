// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData/ItemStructs.h"
#include "SUWInventoryslotInterface.h"
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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Update")
	bool UpdateSlotEvent(FItemData NewItem);
	virtual bool UpdateSlotEvent_Implementation(FItemData NewItem);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetToSelected();
	virtual void SetToSelected_Implementation() {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetToHovered();
	virtual void SetToHovered_Implementation() {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ClearHovered();
	virtual void ClearHovered_Implementation() {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ClearSelected();
	virtual void ClearSelected_Implementation() {};

	UFUNCTION(BlueprintCallable)
	void SetContainedItem(FItemData NewItem) { ContainedItem = NewItem; }
	UFUNCTION(BlueprintPure)
	FItemData GetContainedItem() { return ContainedItem; }

protected:
	UPROPERTY(BlueprintReadOnly)
	FItemData ContainedItem;
};
