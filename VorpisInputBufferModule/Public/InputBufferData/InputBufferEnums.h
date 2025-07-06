#pragma once

#include "InputBufferEnums.generated.h"

UENUM(BlueprintType)
enum class EBufferKey : uint8
{
	EBK_None UMETA(DisplayName = "None"),
	EBK_PrimaryAttack UMETA(DisplayName = "PrimaryAttack"),
	EBK_SecondaryAttack UMETA(DisplayName = "SecondaryAttack"),
	EBK_TertiaryAttack UMETA(DisplayName = "TertiaryAttack"),
	EBK_PrimaryBash UMETA(DisplayName = "PrimaryBash"),
	EBK_SecondaryBash UMETA(DisplayName = "SecondaryBash"),
	EBK_Grapple UMETA(DisplayName = "Grapple"),
	EBK_Dodge UMETA(DisplayName = "Dodge"),
	EBK_Parry UMETA(DisplayName = "Parry"),
	EBK_Jump UMETA(DisplayName = "Jump"),
	EBK_Equip UMETA(DisplayName = "Equip"),
	EBK_UseItem UMETA(DisplayName = "UseItem"),
	EBK_SwitchQuickslotItem UMETA(DisplayName = "SwitchQuickslotItem"),
	EBK_ConsumeItem UMETA(DisplayName = "ConsumeItem"),
	EBK_Interact UMETA(DisplayName = "Interact"),
	EBK_ToggleCombatMode UMETA(DisplayName = "ToggleCombatMode"),
	EBK_GetUp UMETA(DisplayName = "GetUp"),
	EBK_ActivateLeftHandTool UMETA(DisplayName = "ActivateLeftHandTool"),
	EBK_Zoom UMETA(DisplayName = "Zoom"),
	EBK_Aim UMETA(DisplayName = "Aim"),
	EBK_PrimaryLeftHandToolAction UMETA(DisplayName = "PrimaryLeftHandToolAction"),
	EKB_SecondaryLeftHandToolAction UMETA(DisplayName = "SecondaryLeftHandToolAction"),
	EBK_TertiaryLeftHandToolAction UMETA(DisplayName = "TertiaryLeftHandToolAction"),
	EBK_PrimaryWorkAction UMETA(DisplayName = "PrimaryWorkAction"),
	EKB_SecondaryWorkAction UMETA(DisplayName = "SecondaryWorkAction"),
	EBK_TertiaryWorkAction UMETA(DisplayName = "TertiaryWorkAction"),
	EBK_ToggleInventory UMETA(DisplayName = "OpenInventory"),
	EBK_PutItemAway UMETA(DisplayName = "PutItemAway"),
	EBK_Grab UMETA(DisplayName = "Grab"),
	EBK_SwitchLeftHandToolRight UMETA(DisplayName = "SwitchLeftHandToolRight"),
	EBK_SwitchLeftHandToolLeft UMETA(DisplayName = "SwitchLeftHandToolLeft"),
	EBK_AdjustLeftHandTool UMETA(DisplayName = "AdjustLeftHandTool"),
	EBK_PutAwayLeftHandTool UMETA(DisplayName = "PutAwayLeftHandTool"),
	EBK_Kick UMETA(DisplayName = "Kick"),
	EBK_LeftHandSecondaryAction UMETA(DisplayName = "LeftHandSecondaryAction"),
};

UENUM(BlueprintType)
enum class EAuxBufferKey : uint8
{
	EABK_None UMETA(DisplayName = "None"),
	EABK_Forward UMETA(DisplayName = "Forward"),
	EABK_Back UMETA(DisplayName = "Back"),
	EABK_Left UMETA(DisplayName = "Left"),
	EABK_Right UMETA(DisplayName = "Right"),
	EABK_HoldingHotkeyButton UMETA(DisplayName = "HoldingHotKeyButton"),
};