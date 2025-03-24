// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent/EquipmentComponent.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentComponent::RecieveQuickslots(TMap<int, FItemData> QuickslotsToRecieve)
{
	Quickslots = QuickslotsToRecieve;
}

void UEquipmentComponent::SetDefaultQuickslots()
{
	if (!IsValid(BlankAsset)) {
		UE_LOG(LogTemp, Error, TEXT("BlankAsset not set in EquipmentComponent!"));
		return;
	}
	for (int i = 0; i < QuickslotsLength; i++) {
		FItemData BlankItem;
		BlankItem.ItemAsset = BlankAsset;
		Quickslots.Add(i, BlankItem);
	}
}

void UEquipmentComponent::InitializeQuickslots()
{
	 // so what we need to do here is itereate through the quickslots and call the delagate so taht it spawn on the player
	for (int i = 0; i < QuickslotsLength; i++) {
		if (!IsValid(Quickslots[i].ItemAsset)) continue;
		if (Quickslots[i].ItemAsset != BlankAsset) {
			AffectEquipmentStaticMeshes.Broadcast(Quickslots[i], true);
		}
	}
}


void UEquipmentComponent::EquipItem(FItemData ItemData, EEquipmentSlot Slot)
{
	if (GetIsSlotEmpty(Slot)) {
		UE_LOG(LogTemp, Warning, TEXT("slot was empty"))
		EquippedItems.Add(Slot, ItemData);
		if (Slot == EEquipmentSlot::EES_RightHand) {
			EquippedRightHandItem = ItemData;
		} else if (Slot == EEquipmentSlot::EES_LeftHand) {
			EquippedLeftHandItem = ItemData;
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("slot was not empty"))
	// error toast
	}
}

FItemData UEquipmentComponent::GetEquippedItem(EEquipmentSlot Slot)
{
	if (EquippedItems.Contains(Slot)) {
		return EquippedItems[Slot];
	} else {
		return FItemData();
	}
}

bool UEquipmentComponent::GetIsSlotEmpty(EEquipmentSlot Slot)
{
	FItemData FoundItem = GetEquippedItem(Slot);
	return !IsValid(FoundItem.ItemAsset);
}

FItemData UEquipmentComponent::UnequipItem(EEquipmentSlot Slot)
{
		FItemData ItemToReturn = EquippedItems[Slot];
		EquippedItems.Remove(Slot);
		if (Slot == EEquipmentSlot::EES_RightHand) {
			EquippedRightHandItem = FItemData();
		}
		else if (Slot == EEquipmentSlot::EES_LeftHand) {
			EquippedLeftHandItem = FItemData();
		}
		return ItemToReturn;
}

FItemData UEquipmentComponent::SwapItem(EEquipmentSlot Slot, FItemData ItemToUse)
{
	if (GetIsSlotEmpty(Slot)) {
		EquipItem(ItemToUse, Slot);
		return FItemData();
	} else {
		FItemData ItemToReturn = EquippedItems[Slot];
		EquippedItems[Slot] = ItemToUse;
		return ItemToReturn;
	}
}

// quickslots

bool UEquipmentComponent::GetIsQuickslotEmpty(int Slot)
{
	FItemData FoundItem = GetQuickslot(Slot);

	return IsValid(FoundItem.ItemAsset) || FoundItem.ItemAsset == BlankAsset;
}

int UEquipmentComponent::FindStackableItemInQuickslot(FItemData ItemData)
{
	for (int i = 0; i < QuickslotsLength; i++) {
		if (Quickslots[i].IsFull) {
			continue;
		}
		if (Quickslots[i].ItemAsset == ItemData.ItemAsset) {
			return i;
		}
	}
	return -1;
}

// item amount 8
// max size 10
// available space 2
// 
//

EStackableRejectionReason UEquipmentComponent::AddStackableItemToQuickslot(int ItemAmount, int Slot) {
	if (Quickslots[Slot].ItemAsset->IsStackable) {
		if (Quickslots[Slot].ItemAsset->MaxStackSize <= (Quickslots[Slot].Amount + ItemAmount)) {
			Quickslots[Slot].Amount += ItemAmount;
			return EStackableRejectionReason::ESRR_None;
		}
		else {
			int AvailableSpace = Quickslots[Slot].ItemAsset->MaxStackSize - Quickslots[Slot].Amount;
			int ItemAmountMinusAvailableSpace = ItemAmount - AvailableSpace;
			Quickslots[Slot].Amount = Quickslots[Slot].ItemAsset->MaxStackSize;
			LeftOverItemAmount = ItemAmountMinusAvailableSpace;
			return EStackableRejectionReason::ESRR_StackLimitReached;
		}
	}
	return EStackableRejectionReason::ESRR_NotStackable;
}

void UEquipmentComponent::AddItemToQuickslots(FItemData ItemData, int Slot)
{
	if (!IsValid(ItemData.ItemAsset)) return;
	if (ItemData.ItemAsset == BlankAsset) return;
	if (ItemData.ItemAsset->IsStackable) {
		int FoundSlot = FindStackableItemInQuickslot(ItemData);
		if (FoundSlot != -1) {
			EStackableRejectionReason RejectionReason = AddStackableItemToQuickslot(ItemData.Amount, Slot);
			switch (RejectionReason) {
			case EStackableRejectionReason::ESRR_None:
				return;
			case EStackableRejectionReason::ESRR_StackLimitReached:
				ItemData.Amount = LeftOverItemAmount;
				AddItemToQuickslots(ItemData, Slot);
				return;
			}
		}	else {
			// error toast
		}
	}
	if (GetIsQuickslotEmpty(Slot)) {
		Quickslots.Add(Slot, ItemData);
	}
	else {
		// error toast
		UE_LOG(LogTemp, Warning, TEXT("Quickslot %d is not empty!"), Slot);
	}

}

int UEquipmentComponent::GetFirstEmptyQuickslot()
{
	for (int i = 0; i < QuickslotsLength; i++) {
		if (GetIsQuickslotEmpty(i)) {
			return i;
		}
	}
	return -1;
}

FItemData UEquipmentComponent::GetQuickslot(int Slot)
{
	return Quickslots[Slot];
}

FItemData UEquipmentComponent::RemoveQuickslot(int Slot)
{
	if (GetIsQuickslotEmpty(Slot)) {
		return FItemData();
	}
	else {
		FItemData ItemToReturn = Quickslots[Slot];
		FItemData BlankItem;
		BlankItem.ItemAsset = BlankAsset;
		Quickslots[Slot] = BlankItem;
		return ItemToReturn;
	}
}

FItemData UEquipmentComponent::SwapQuickslot(int slot, FItemData ItemToUse)
{
	if (GetIsQuickslotEmpty(slot)) {
		UEquipmentComponent::AddItemToQuickslots(ItemToUse, slot);
		return FItemData();
	}
	else {
		FItemData ItemToReturn = Quickslots[slot];
		Quickslots[slot] = ItemToUse;
		return ItemToReturn;
	}
}







// interfaces

void UEquipmentComponent::InterfaceEquipItem(FItemData ItemData, EEquipmentSlot Slot)
{
	UEquipmentComponent::EquipItem(ItemData, Slot);
}
FItemData UEquipmentComponent::InterfaceGetEquippedItem(EEquipmentSlot Slot)
{
	return UEquipmentComponent::GetEquippedItem(Slot);
}
bool UEquipmentComponent::InterfaceGetIsSlotEmpty(EEquipmentSlot Slot)
{
	return UEquipmentComponent::GetIsSlotEmpty(Slot);
}
FItemData UEquipmentComponent::InterfaceUnequipItem(EEquipmentSlot Slot)
{
	return UEquipmentComponent::UnequipItem(Slot);
}
FItemData UEquipmentComponent::InterfaceSwapItem(EEquipmentSlot Slot, FItemData ItemToUse)
{
	return UEquipmentComponent::SwapItem(Slot, ItemToUse);
}

void UEquipmentComponent::InterfaceAddItemToQuickslots(FItemData ItemData, int Slot)
{
	UEquipmentComponent::AddItemToQuickslots(ItemData, Slot);
}
int UEquipmentComponent::InterfaceGetFirstEmptyQuickslot()
{
	return UEquipmentComponent::GetFirstEmptyQuickslot();
}
FItemData UEquipmentComponent::InterfaceGetQuickslot(int Slot)
{
	return UEquipmentComponent::GetQuickslot(Slot);
}
FItemData UEquipmentComponent::InterfaceRemoveQuickslot(int Slot)
{
	return UEquipmentComponent::RemoveQuickslot(Slot);
}
FItemData UEquipmentComponent::InterfaceSwapQuickslot(int slot, FItemData ItemToUse)
{
	return UEquipmentComponent::SwapQuickslot(slot, ItemToUse);
}
bool UEquipmentComponent::InterfaceGetIsQuickslotEmpty(int Slot)
{
	return UEquipmentComponent::GetIsQuickslotEmpty(Slot);
}

void UEquipmentComponent::IncrementSelectedQuickslot()
{
	if (SelectedQuickslot + 1 < QuickslotsLength) {
		SelectedQuickslot++;
	}
	else {
		SelectedQuickslot = 0;
	}
}
void UEquipmentComponent::DecrementSelectedQuickslot()
{
	if (SelectedQuickslot - 1 >= 0) {
		SelectedQuickslot--;
	}
	else {
		SelectedQuickslot = QuickslotsLength - 1;
	}
}