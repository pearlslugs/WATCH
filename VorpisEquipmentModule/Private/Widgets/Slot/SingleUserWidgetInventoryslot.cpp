// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/slot/SingleUserWidgetInventoryslot.h"


bool USingleUserWidgetInventoryslot::UpdateSlotEvent_Implementation(FItemData NewItem)
{
	// use in blueprint
	UE_LOG(LogTemp, Warning, TEXT("USingleUserWidgetInventoryslot::UpdateSlotEvent_Implementation"));
	return false;
}