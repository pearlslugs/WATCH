// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInterface/BaseRpgCharacterInterface.h"

// Add default functionality here for any IBaseRpgCharacterInterface functions that are not pure virtual.
USkinnedMeshComponent* IBaseRpgCharacterInterface::GetSkinnedMesh()
{
	return nullptr;
}

bool IBaseRpgCharacterInterface::IsDead()
{
	return false;
}

void IBaseRpgCharacterInterface::InterfaceSetCharacterCombatState_Implementation(ECombatState NewState)
{

}

void IBaseRpgCharacterInterface::InterfaceSetCharacterGeneralState_Implementation(EGeneralState NewState)
{

}

void IBaseRpgCharacterInterface::RotateTowardsTarget_Implementation(bool State)
{

}

void IBaseRpgCharacterInterface::InterfaceToggleWeaponCollision_Implementation(bool State)
{

}

void IBaseRpgCharacterInterface::InterfacePopulateInitialAttackData_Implementation(FInitialAttackData InitialAttackData)
{

}