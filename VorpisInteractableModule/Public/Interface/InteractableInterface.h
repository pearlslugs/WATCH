// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemData/ItemStructs.h"
#include "CharacterStateData/CharacterStateEnums.h"
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
	virtual bool IsInteractable() { return false; }
	virtual void ToggleHovered(bool Hovered) {}
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	FItemData GetHeldItem();
	virtual FItemData GetHeldItem_Implementation() { return FItemData(); };
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	//void ThirdInteract(AActor* Interactor);
	//virtual void ThirdInteract_Implementation(AActor* Interactor);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void DestroyInteractable();
	virtual void DestroyInteractable_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	ETaskState GetTaskType();
	virtual ETaskState GetTaskType_Implementation() { return ETaskState::ETS_None; };

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void ActivateDecal(FTransform DecalPosition);
	virtual void ActivateDecal_Implementation(FTransform DecalPosition) {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void ToggleCollision(bool Condition);
	virtual void ToggleCollision_Implementation(bool Condition) {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void ScaleInteractable(float NewScale);
	virtual void ScaleInteractable_Implementation(float NewScale) {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void RotateToTarget(FVector Target);
	virtual void RotateToTarget_Implementation(FVector Target) {};
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void PourLiquid(FVector PourTarget);
	virtual void PourLiquid_Implementation(FVector PourTarget) {};
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void CreatePourGoal(FVector GoalLocation);
	virtual void CreatePourGoal_Implementation(FVector GoalLocation) {};
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void DestroyParticles();
	virtual void DestroyParticles_Implementation() {};
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void SetPhysics(bool Condition);
	virtual void SetPhysics_Implementation(bool Condition) {};
};
