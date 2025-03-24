// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/QuickslotsUserWidget.h"

bool UQuickslotsUserWidget::UpdateSlot(FItemData NewItem, int QuickslotIndex)
{
	if (QuickslotIndex < 0 || QuickslotIndex >= Quickslots.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Quickslot index out of range"));
		return false;
	}
	return Quickslots[QuickslotIndex]->UpdateSlotEvent(NewItem);
}