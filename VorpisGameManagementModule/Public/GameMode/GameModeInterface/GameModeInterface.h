// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemData/ItemStructs.h"
#include "GameModeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VORPISGAMEMANAGEMENTMODULE_API IGameModeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void InterfaceSaveNewPickUp(FPickUpData ItemToSave) = 0;
	virtual TMap<FGuid, FPickUpData> InterfaceLoadAllPickups() = 0;
};
