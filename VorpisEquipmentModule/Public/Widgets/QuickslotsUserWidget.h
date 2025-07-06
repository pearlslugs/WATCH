// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData/ItemStructs.h"
#include "QuickslotsInterface/QuickslotsInterface.h"
#include "BaseInterface/BaseWidgetInterface.h"
#include "Slot/SingleUserWidgetInventoryslot.h"
#include "QuickslotsUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHoveredSet, int, HoveredIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedSet, int, SelectedIndex);

/**
 * 
 */
UCLASS()
class VORPISEQUIPMENTMODULE_API UQuickslotsUserWidget : public UUserWidget, public IBaseWidgetInterface, public IQuickslotsInterface
{
	GENERATED_BODY()
public:
	// delegates
	UPROPERTY(BlueprintAssignable)
	FOnHoveredSet OnHoveredSet;
	UPROPERTY(BlueprintAssignable)
	FOnSelectedSet OnSelectedSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Equipment")
	UActorComponent* EquipmentComponent;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int SelectedIndex = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int HoveredIndex = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int PreviousSelected;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int PreviousHovered;
	UFUNCTION(BlueprintCallable)
	void SetSelectedIndex(int NewSelected) { SelectedIndex = NewSelected; }
	UFUNCTION(BlueprintCallable)
	void SetHoveredIndex(int NewHovered) { HoveredIndex = NewHovered; }
	UFUNCTION(BlueprintCallable)
	void SetPreviousSelectedIndex(int NewSelected) { PreviousSelected = NewSelected; }
	UFUNCTION(BlueprintCallable)
	void SetPreviousHoveredIndex(int NewHovered) { PreviousHovered = NewHovered; }
	
	UFUNCTION()
	int KeepIndexInBounds(bool Incriment);
	UFUNCTION(BlueprintCallable)
	void InitializeQuickslots(TArray<FItemData> CurrentEquipment);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	int MaxQuickslots = 6;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	TArray<USingleUserWidgetInventoryslot*> Quickslots;
	UFUNCTION(BlueprintCallable)
	void BroadcastHoveredSet();
	UFUNCTION(BlueprintCallable)
	void BroadcastSelectedSet();


	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool UpdateSlot(FItemData NewItem, int QuickslotIndex);

	// interfaces
	virtual void WidgetLeftInput_Implementation() override;
	virtual void WidgetRightInput_Implementation() override;
	virtual void UpdateSlotInterface_Implementation(FItemData Item, int NewSlot) override;
};
