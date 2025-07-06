// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/QuickslotsUserWidget.h"

bool UQuickslotsUserWidget::UpdateSlot(FItemData NewItem, int QuickslotIndex)
{
	if (QuickslotIndex < 0 || QuickslotIndex >= Quickslots.Num())
	{
		return false;
	}
	return Quickslots[QuickslotIndex]->UpdateSlotEvent(NewItem);
}

int UQuickslotsUserWidget::KeepIndexInBounds(bool Incriment)
{
	int AmountToAdd = Incriment ? 1 : -1;
	if (HoveredIndex + AmountToAdd >= MaxQuickslots) {
		return 0;
	}
	else if (HoveredIndex + AmountToAdd < 0) {
		return MaxQuickslots - 1;
	}
	else {
		return HoveredIndex + AmountToAdd;
	}
}

void UQuickslotsUserWidget::WidgetLeftInput_Implementation()
{
	PreviousHovered = HoveredIndex;
	int NewHovered = UQuickslotsUserWidget::KeepIndexInBounds(false);
	HoveredIndex = NewHovered;
	OnHoveredSet.Broadcast(HoveredIndex);
	Quickslots[NewHovered]->SetToHovered();
	Quickslots[PreviousHovered]->ClearHovered();
}
void UQuickslotsUserWidget::WidgetRightInput_Implementation()
{
	PreviousHovered = HoveredIndex;
	int NewHovered = UQuickslotsUserWidget::KeepIndexInBounds(true);
	HoveredIndex = NewHovered;
	OnHoveredSet.Broadcast(HoveredIndex);
	Quickslots[NewHovered]->SetToHovered();
	Quickslots[PreviousHovered]->ClearHovered();
}

void UQuickslotsUserWidget::InitializeQuickslots(TArray<FItemData> CurrentEquipment)
{
	int Index = 0;
	for (FItemData Item : CurrentEquipment)
	{
		if (Index > MaxQuickslots) return;
		UpdateSlot(Item, Index);
		Index++;
	}
}

void UQuickslotsUserWidget::UpdateSlotInterface_Implementation(FItemData Item, int NewSlot)
{
	UQuickslotsUserWidget::UpdateSlot(Item, NewSlot);
}

void UQuickslotsUserWidget::BroadcastHoveredSet()
{
	OnHoveredSet.Broadcast(HoveredIndex);
}
void UQuickslotsUserWidget::BroadcastSelectedSet()
{
	OnSelectedSet.Broadcast(SelectedIndex);
}