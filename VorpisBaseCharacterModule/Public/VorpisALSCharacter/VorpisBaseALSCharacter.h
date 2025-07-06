// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AlsCharacter.h"
#include "AlsCameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Utility/AlsMath.h"
#include "GameFramework/PlayerController.h"
#include "VorpisBaseALSCharacter.generated.h"


struct FInputActionValue;
class UAlsCameraComponent;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class VORPISBASECHARACTERMODULE_API AVorpisBaseALSCharacter : public AAlsCharacter
{
	GENERATED_BODY()

protected:
	FTimerHandle DelayJumpTimer;
	float DelayJumpTime = 0.1f;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Als Character Example")
	TObjectPtr<UAlsCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> LookMouseAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> SprintAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> WalkAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> CrouchAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> AimAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> RagdollAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> RollAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> RotationModeAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> ViewModeAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> SwitchShoulderAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> LockOnAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> PrimaryAttackAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> PrimaryWorkAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> DodgeAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> SecondaryAttackAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> SecondaryWorkAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> TeretiaryAttackAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> TeretiaryWorkAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> ActivateLeftHandToolAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> LeftHandToolPrimaryAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> LeftHandToolSecondaryAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> LeftHandToolTertiaryAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> ParryAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> GrabAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> QuickslotRightAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> QuickslotLeftAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> MenuNavigateAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> EquipAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> MenuRightAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> MenuLeftAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> MenuUpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> MenuDownAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> InteractAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> InventoryAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> UpDPadAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> DownDPadAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> UpMacroROneAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> DownMacroROneAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> UpMacroRTwoAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> DownMacroRTwoAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> UpMacroLOneAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> DownMacroLOneAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> UpMacroLTwoAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> DownMacroLTwoAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> KickAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> MenuSelectAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction>RightHandTaskPrimaryAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction>RightHandTaskSecondaryAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction>MashTaskInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input", Meta = (ClampMin = 0, ForceUnits = "x"))
	float LookUpMouseSensitivity{ 3.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input", Meta = (ClampMin = 0, ForceUnits = "x"))
	float LookRightMouseSensitivity{ 3.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input",
		Meta = (ClampMin = 0, ForceUnits = "deg/s"))
	float LookUpRate{ 90.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input",
		Meta = (ClampMin = 0, ForceUnits = "deg/s"))
	float LookRightRate{ 240.0f };

public:
	AVorpisBaseALSCharacter();

	virtual void NotifyControllerChanged() override;
	UFUNCTION(BlueprintCallable)
	virtual void Input_OnMove(const FInputActionValue& ActionValue);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool DisableWalking = false;
	UFUNCTION(BlueprintCallable)
	void SetDisableWalking(bool NewCondition) { DisableWalking = NewCondition; };
	// Camera

protected:
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& ViewInfo) override;

	// Input

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* Input) override;

	virtual void Input_OnLookMouse(const FInputActionValue& ActionValue);

	virtual void Input_OnLook(const FInputActionValue& ActionValue);

private:
	virtual void Input_OnSprint(const FInputActionValue& ActionValue);

	virtual void Input_OnWalk();

	virtual void Input_OnCrouch();

	virtual void Input_OnJump(const FInputActionValue& ActionValue);

	virtual void Input_OnAim(const FInputActionValue& ActionValue);

	virtual void Input_OnRagdoll();

	virtual void Input_OnRoll();

	virtual void Input_OnRotationMode();

	virtual void Input_OnViewMode();

	virtual void Input_OnSwitchShoulder();
	// Debug

public:
	virtual void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& Unused, float& VerticalLocation) override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsLockedOnLocomotion = false;
	UFUNCTION(BlueprintPure)
	bool GetIsLockedOnLocomotion() { return IsLockedOnLocomotion; };
	UFUNCTION(BlueprintCallable)
	void SetIsLockedOnLocomotion(bool NewCondition) { IsLockedOnLocomotion = NewCondition; };
	UFUNCTION(BlueprintCallable)
	void StartLockedOnLocomotion();
	UFUNCTION(BlueprintCallable)
	void StopLockedOnLocomotion();

	UFUNCTION(BlueprintCallable)
	void StartJumping();
};
