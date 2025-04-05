// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RpgCharacter/BaseRpgCharacter.h"
#include "BaseCombatComponent/BaseCombatComponent.h"
#include "CombatData/CombatStructs.h"
#include "EquipmentComponent/EquipmentComponent.h"
#include "InputBufferData/InputBufferEnums.h"
#include "WeaponCollisionComponent/WeaponCollisionComponent.h"
#include "EnhancedInputComponent.h"
#include "CharacterStateComponent/CharacterStateComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MontageManagerComponent/MontageManagerComponent.h"
#include "InteractorComponent/InteractorComponent.h"
#include "LockOnComponent/LockOnComponent.h"
#include "CharacterStateData/CharacterStateEnums.h"
#include "PlayerCharacter/VorpisPlayerCharacterInterface.h"
#include "InputBufferComponent/VorpisUncursedInputBufferComponent.h"
#include "VorpisBasePlayerCharacter.generated.h"

/**
 * 
 */



struct FInputActionValue;
struct FHitTraceResults;
class UAlsCameraComponent;
class UInputMappingContext;
class UInputAction;
class UPlayerDialogueComponent;
class AVorpisPlayerController;
class UUserWidget;
class UDialogueDataAsset;


UCLASS()
class VORPISPLAYERMODULE_API AVorpisBasePlayerCharacter : public ABaseRpgCharacter, public IVorpisPlayerCharacterInterface
{
	GENERATED_BODY()

public:
	AVorpisBasePlayerCharacter();

	// timers
	FTimerHandle ResetBufferTimer;
	float ResetInputBufferTime = 0.4f;
	UFUNCTION()
	void ResetInputBuffer();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* Input) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UInteractorComponent* InteractorComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	ULockOnComponent* LockOnComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UVorpisUncursedInputBufferComponent* UncursedInputBufferComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPlayerDialogueComponent* PlayerDialogueComponent;



	// Controller and cameera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	AVorpisPlayerController* PlayerController = nullptr;

	// input
	UFUNCTION()
	void InputBufferKey(EBufferKey Key);
	UFUNCTION()
	void OnInputConsumed(EBufferKey Key);

	// input
	virtual void Input_OnLookMouse(const FInputActionValue& ActionValue);
	virtual void Input_OnLook(const FInputActionValue& ActionValue);

private:

	// Buffer
	UFUNCTION()
	void BufferDodge();
	UFUNCTION()
	void BufferKick();
	UFUNCTION()
	void BufferPrimaryAttack();
	UFUNCTION()
	void BufferJump(const FInputActionValue& ActionValue);

	// combat
	UFUNCTION()
	void LockOn(const FInputActionValue& ActionValue);
	UFUNCTION()
	void Dodge();
	UFUNCTION()
	void PrimaryAttack();
	UFUNCTION()
	void Kick();
	UFUNCTION()
	void OnComboFinished();

	// lock on
	UFUNCTION()
	void OnLockedOn(bool IsLockedOn);

	// menus
	UFUNCTION()
	void SelectInMenu();

	//  state
	UFUNCTION()
	void ResetState();

public:

	// interfaces
	virtual void CloseInputBuffer_Implementation() override;
	virtual void OpenInputBuffer_Implementation() override;
	virtual void InterfaceSetCharacterGeneralState_Implementation(EGeneralState NewState) override;
	virtual void InterfaceSetCharacterCombatState_Implementation(ECombatState NewCombatState) override;
	virtual void RotateTowardsTarget_Implementation(bool State) override;
	virtual void ToggleSelectedEquipmentEquipped_Implementation(bool State) override;
	virtual void InterfacePopulateInitialAttackData_Implementation(FInitialAttackData InitialAttackData) override;
	virtual void MountDialogueComponentAndSetAsset_Implementation(UDialogueDataAsset* AssetToMount, UUserWidget* Widget) override;
	// use this on the bp interface
	UFUNCTION(BlueprintCallable)
	void MountNewDialogue(UDialogueDataAsset* AssetToMount, UUserWidget* Widget);
	// controller interfaces
	virtual void ControllerInputDown() override {};
	virtual void ControllerInputUp() override {};
	virtual void ControllerInputLeft() override {};
	virtual void ControllerInputRight() override {};
	virtual void ControllerInputSelect() override {};
	virtual void ControllerInputBack() override {};
	virtual void ControllerInputStart() override {};
};
