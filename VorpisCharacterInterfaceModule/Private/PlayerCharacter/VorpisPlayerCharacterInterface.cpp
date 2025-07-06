// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/VorpisPlayerCharacterInterface.h"

// Add default functionality here for any IVorpisPlayerCharacterInterface functions that are not pure virtual.
void IVorpisPlayerCharacterInterface::CloseInputBuffer_Implementation()
{
	// implement
}

void IVorpisPlayerCharacterInterface::OpenInputBuffer_Implementation()
{
	// implement
}

void IVorpisPlayerCharacterInterface::ToggleSelectedEquipmentEquipped_Implementation(bool State)
{
	// implement
}

TArray<FItemData> IVorpisPlayerCharacterInterface::GetEquippedItems_Implementation()
{
	TArray<FItemData> Empty;
	return Empty;
}