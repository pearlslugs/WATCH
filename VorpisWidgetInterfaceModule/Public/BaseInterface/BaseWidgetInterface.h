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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Widget")
	void WidgetUpInput();
	virtual void WidgetUpInput_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Widget")
	void WidgetDownInput();
	virtual void WidgetDownInput_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Widget")
	void WidgetLeftInput();
	virtual void WidgetLeftInput_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Widget")
	void WidgetRightInput();
	virtual void WidgetRightInput_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Widget")
	void WidgetSelectInput();
	virtual void WidgetSelectInput_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Widget")
	void WidgetBackInput();
	virtual void WidgetBackInput_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Widget")
	void SetContent(const FString& Content);
	virtual void SetContent_Implementation(const FString& Content) {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Widget")
	void CloseWidget();
	virtual void CloseWidget_Implementation() {};
};
