// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VORPISINTERACTABLEMODULE_API IInteractableInterface
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void Interact(AActor* Interactor);
	virtual void Interact_Implementation(AActor* Interactor);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void SecondaryInteract(AActor* Interactor);
	virtual void SecondaryInteract_Implementation(AActor* Interactor);
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	//void ThirdInteract(AActor* Interactor);
	//virtual void ThirdInteract_Implementation(AActor* Interactor);
};
