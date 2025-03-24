// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BaseWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBaseWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VORPISWIDGETINTERFACEMODULE_API IBaseWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void WidgetUpInput();
	virtual void WidgetDownInput();
	virtual void WidgetLeftInput();
	virtual void WidgetRightInput();
	virtual void WidgetSelectInput();
	virtual void WidgetBackInput();
	virtual void SetContent(FString Content) {};
	virtual void CloseWidget() {};
};
