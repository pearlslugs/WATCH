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
#include "Components/BoxComponent.h"
#include "CharacterStateData/CharacterStateEnums.h"
#include "PlayerCharacter/VorpisPlayerCharacterInterface.h"
#include "InputBufferComponent/VorpisUncursedInputBufferComponent.h"
#include "VorpisBasePlayerCharacter.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreateToast, FString, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRotationReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateOverlay);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

//*****************************************************
//
//				HAND IK IDEAS
//		Right Hand Controls: Input_OnLook The mouse effects the right hand ik
//		Left Hand Controls:	Input_OnMove. the movement input controls the left hand
//		so WASD move it on k&m, the left stick moves in on controller
// 
// 
//		Two different types of hand ik enabled
//		The mamin difference is that one mode up and down move the hand up and down, 
//		the other mode moves it towards and away from the player
// 
//		Other idea
//		use trigger and bumper to move back and forth, well see
//
//******************************************************
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnableHandIK, EHandIkState, HandIKState);



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

	UPROPERTY(BlueprintAssignable)
	FOnCreateToast OnCreateToastError;
	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdated OnInventoryUpdated;
	UPROPERTY(BlueprintAssignable)
	FOnUpdateOverlay OnUpdateOverlay;
	UPROPERTY(BlueprintAssignable)
	FOnRotationReached OnRotationReached;
	UPROPERTY(BlueprintAssignable)
	FEnableHandIK EnableHandIK;
	UFUNCTION()
	void ClearRotationReagedDelegate();

	// timers
	FTimerHandle ResetBufferTimer;
	float ResetInputBufferTime = 0.4f;
		// rotation timer
	FTimerHandle RotateToTargetTimer;
	float RotateToTargetTime = 0.01f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float RotationSpeed = 45.f;
	FTimerHandle MashProgressChecker;
	float MashProgressCheckerTime = 0.02f;
	UPROPERTY()
	float MashProgress = 0.01f;
	UPROPERTY()
	float MashTime = 0.01f;
	UPROPERTY(BlueprintReadOnly)
	float MashOutput = 0.01f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MashProgressIncrimentValue = 0.2f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ProgressLossDecriment = 0.01f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MashTimeIncimentTimerValue = 0.05f;
	UPROPERTY(BlueprintReadOnly)
	bool InMashTask;
	UFUNCTION(BlueprintCallable)
	void StopMashTask();
	UFUNCTION(BlueprintCallable)
	void SetInMashTask(bool NewCondition) { InMashTask = NewCondition; }
	UFUNCTION(BlueprintCallable)
	void StartCheckingMashProgress();
	UFUNCTION()
	void AssessMashingProgress();
	UFUNCTION()
	void MashTaskAction();
	UPROPERTY()
	FVector RotateTargetLocation;
	UFUNCTION(BlueprintCallable)
	void SetRotationTarget(FVector NewTargetLocation);
	UPROPERTY()
	FRotator RotationTarget;
	UFUNCTION(BlueprintCallable)
	void RotateToTarget();

	UFUNCTION()
	void ResetInputBuffer();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float IKTargetMaxX = 50.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float IKTargetMaxY = 50.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float IKTargetMinX = -50.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float IKTargetMinY = -50.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float IKTargetMovementSale = 2.f;
	UFUNCTION(BlueprintCallable)
	void SetDisableLookControls(bool NewCondition) { DisableLookControls = NewCondition; }
	UFUNCTION(BlueprintPure)
	bool GetDisableLookControls() { return DisableLookControls; }

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	EHandIkState RightHandIKState;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	EHandIkState LeftHandIKState;
	UFUNCTION(BlueprintCallable)
	void SetRightHandIKstate(EHandIkState NewState) { RightHandIKState = NewState; }
	UFUNCTION(BlueprintCallable)
	void SetLeftHandIKstate(EHandIkState NewState) { LeftHandIKState = NewState; }
	UFUNCTION(BlueprintCallable)
	void SetTwistScrewActive(bool NewCondition) { TwistScrewActive = NewCondition; }
	UFUNCTION(BlueprintPure)
	bool GetTwistScrewActive() { return TwistScrewActive; }


	UFUNCTION(BlueprintCallable)
	void SetRightHandTargetVector(FVector NewTarget) { RightHandTargetVector = NewTarget; }
	UFUNCTION(BlueprintCallable)
	void SetRightHandTargetRotator(FRotator NewTarget) { RightHandTargetRotator = NewTarget; }
	UFUNCTION(BlueprintPure)
	FRotator GetRightHandTargetRotator() { return RightHandTargetRotator;}
	UFUNCTION(BlueprintCallable)
	void SetItemToPickUp(FItemData NewItem) { ItemToPickUp = NewItem; }
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* LeftShoulderTraceLocation;

	// pick  up
	UFUNCTION(BlueprintPure)
	FItemData GetItemToPickUp() { return ItemToPickUp; }

	// tasks
	UPROPERTY(EditAnywhere)
	float DistanceToMoveFromTarget = 85.f;
	UPROPERTY(EditAnywhere)
	float RotationTargetZOffset = -10.f;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK")
	FVector RightHandTargetVector = FVector();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK")
	FRotator RightHandTargetRotator = FRotator();
	UPROPERTY(BlueprintReadOnly)
	bool FuelPlantPickedUp;


	// Controller and cameera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	AVorpisPlayerController* PlayerController = nullptr;

	//  state
	UFUNCTION(BlueprintCallable)
	void ResetState();

	// input
	UFUNCTION()
	void InputBufferKey(EBufferKey Key);
	UFUNCTION()
	void OnInputConsumed(EBufferKey Key);
	UFUNCTION()
	void MoveRightHandIKTarget(FVector2D Vector);
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RightHandIKTargetCurrentX;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RightHandIKTargetCurrentY;
	UFUNCTION()
	void MoveRightHand(FVector2D Input, bool UseMouse);

	UPROPERTY(BlueprintReadOnly)
	bool TwistScrewActive;

	UFUNCTION(Blueprintcallable)
	void AttachScrewToFruit();
	UFUNCTION(BlueprintCallable)
	void SetFuelPlantPickedUp(bool NewCondition) { FuelPlantPickedUp = NewCondition; };
	UFUNCTION(BlueprintPure)
	bool GetFuelPlantPickedUp() { return FuelPlantPickedUp; }


	EGeneralState GetCharacterGeneralState();

	bool IsDoingTask();

	virtual void Input_OnLookMouse(const FInputActionValue& ActionValue);
	virtual void Input_OnLook(const FInputActionValue& ActionValue);
	virtual void Input_OnMove(const FInputActionValue& ActionValue) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FItemData ItemToPickUp;
	UPROPERTY(BlueprintReadOnly)
	bool DisableLookControls;

private:

	// Buffer
	UFUNCTION()
	void BufferDodge();
	UFUNCTION()
	void BufferKick();
	UFUNCTION()
	void BufferPrimaryAttack();
	UFUNCTION()
	void BufferLeftHandSecondaryUse();
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
	UFUNCTION()
	void CallInteract();
	UFUNCTION()
	void PerformLeftHandSecondaryAction();

	// lock on
	UFUNCTION()
	void OnLockedOn(bool IsLockedOn);

	// menus
	UFUNCTION()
	void SelectInMenu();

	// intneractions
	UFUNCTION()
	void HarvestFuelPlant();
	UFUNCTION(BlueprintCallable)
	void BeginHarvestingFuelPlant();
	UFUNCTION(BlueprintCallable)
	void SetMovementTarget();
	UFUNCTION(BlueprintCallable)
	void SetIKTargetFromActor(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void StartPickingUpItem();

	// ik task
	UFUNCTION()
	void TaskPrimaryAction(const FInputActionValue& ActionValue);
	UFUNCTION()
	void TaskSecondaryAction(const FInputActionValue& ActionValue);
public:

	// native events
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void EquipItemWithToolProperty(EToolProperties Property);
	void EquipItemWithToolProperty_Implementation(EToolProperties Property) {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PerformSecondaryTaskAction(bool InputCondition);
	void PerformSecondaryTaskAction_Implementation(bool InputCondition) {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PerformPrimaryTaskAction(bool InputCondition);
	void PerformPrimaryTaskAction_Implementation(bool InputCondition) {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TwistScrew(FVector2D Input);
	void TwistScrew_Implementation(FVector2D Input) {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PourPlantInToContainer(FVector2D Input, bool UseMouse);
	void PourPlantInToContainer_Implementation(FVector2D Input, bool UseMouse) {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AActor* SpawnPickup(FItemData ItemToSpawn, FTransform Transform);
	AActor* SpawnPickup_Implementation(FItemData ItemToSpawn, FTransform Transform) { return nullptr; };
	// interfaces
	virtual void CloseInputBuffer_Implementation() override;
	virtual void OpenInputBuffer_Implementation() override;
	virtual void InterfaceSetCharacterGeneralState_Implementation(EGeneralState NewState) override;
	virtual void InterfaceSetCharacterCombatState_Implementation(ECombatState NewCombatState) override;
	virtual void RotateTowardsTarget_Implementation(bool State) override;
	virtual void ToggleSelectedEquipmentEquipped_Implementation(bool State) override;
	virtual void InterfacePopulateInitialAttackData_Implementation(FInitialAttackData InitialAttackData) override;
	virtual void MountDialogueComponentAndSetAsset_Implementation(UDialogueDataAsset* AssetToMount, UUserWidget* Widget) override;
	virtual bool CheckToolProperties_Implementation(const TMap<EToolProperties, int32>& RequiredTools) override;
	virtual void StartHarvestingFuelPlant_Implementation(AActor* PlantActor) override;
	virtual void GetPickUp_Implementation(AActor* PickUpActor) override {};
	virtual void FinishPickingUpItem_Implementation(bool RightHand) override;
	virtual TArray<FItemData> GetEquippedItems_Implementation() override;
	virtual void DropItem_Implementation(bool RightHand) override;
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


	// save and load
		// save equipment
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SaveQuickslots();
	void SaveQuickslots_Implementation() {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SaveRightHandItem();
	void SaveRightHandItem_Implementation() {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SaveLeftHandItem();
	void SaveLeftHandItem_Implementation() {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SaveAllEquipment();
	void SaveAllEquipment_Implementation() {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SaveEquipment();
	void SaveEquipment_Implementation() {};
	// load equipment
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void LoadQuickslots();
	void LoadQuickslots_Implementation() {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void LoadRightHandItem();
	void LoadRightHandItem_Implementation() {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void LoadLeftHandItem();
	void LoadLeftHandItem_Implementation() {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void LoadEquipment();
	void LoadEquipment_Implementation() {};
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void LoadAllEquipment();
	void LoadAllEquipment_Implementation() {};
};
