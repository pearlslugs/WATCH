#pragma once

#include "ItemEnums.generated.h"

UENUM(BlueprintType)
enum class EEquipSocketOption : uint8
{
	EESO_None UMETA(DisplayName = "None"),
	EESO_OneHandedWeaponSocket UMETA(DisplayName = "OneHandedWeaponSocket"),
	EESO_TwoHandedBaseGripSocket UMETA(DisplayName = "TwoHandedBaseGripSocket"),
	EESO_TwoHandedPoleGripSocket UMETA(DisplayName = "TwoHandedPoleGripSocket"),
	ESO_LeftHandOneHandedSlot UMETA(DisplayName = "LeftHandOneHandedSlot"),
};

UENUM(BlueprintType)
enum class EUnequipSocketOption : uint8
{
	EUS_None UMETA(DisplayName = "None"),
	EUS_HipSocket UMETA(DisplayName = "HipSocket"),
	EUS_BackSocket UMETA(DisplayName = "BackSocket"),
	EUS_BeltSocket UMETA(DisplayName = "BeltSocket")
};

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	EES_None UMETA(DisplayName = "None"),
	EES_Head UMETA(DisplayName = "Head"),
	EES_Neck UMETA(DisplayName = "Neck"),
	EES_UpperBody UMETA(DisplayName = "Chest"),
	EES_Shoulders UMETA(DisplayName = "Shoulders"),
	EES_Arms UMETA(DisplayName = "Arms"),
	EES_Hands UMETA(DisplayName = "Hands"),
	EES_Legs UMETA(DisplayName = "Legs"),
	EES_Feet UMETA(DisplayName = "Feet"),
	EES_RingOne UMETA(DisplayName = "RingOne"),
	EES_RingTwo UMETA(DisplayName = "RingTwo"),
	EES_Pendant UMETA(DisplayName = "Pendant"),
	EES_BackPack UMETA(DisplayName = "BackPack"),
	EES_WaistPack UMETA(DisplayName = "WaistPack"),
	EES_RightHand UMETA(DisplayName = "RightHand"),
	EES_LeftHand UMETA(DisplayName = "LeftHand"),
};

UENUM(BlueprintType)
enum class EMaterialType : uint8
{
	EMT_None UMETA(DisplayName = "None"),
	EMT_Copper UMETA(DisplayName = "Copper"),
	EMT_Bronze UMETA(DisplayName = "Bronze"),
	EMT_Iron UMETA(DisplayName = "Iron"),
	EMT_Steel UMETA(DisplayName = "Steel"),
	EMT_Tungsten UMETA(DisplayName = "Tungsten"),
	EMT_Silver UMETA(DisplayName = "Silver"),
	EMT_Leather UMETA(DisplayName = "Leather"),
	EMT_Cloth UMETA(DisplayName = "Cloth"),
	EMT_Wood UMETA(DisplayName = "Wood"),
	EMT_Stone UMETA(DisplayName = "Stone"),
	EMT_NotRelavant UMETA(DisplayName = "NotRelavant")
};

UENUM(BlueprintType)
enum class EConsumableType : uint8
{
	ECT_None UMETA(DisplayName = "None"),
	ECT_Throwable UMETA(DisplayName = "Throwable"),
	ECT_Eatible UMETA(DisplayName = "Eatible"),
	ECT_Drinkable UMETA(DisplayName = "Drinkable"),
	ECT_Applicable UMETA(DisplayName = "Applicable")
};

UENUM(BlueprintType)
enum class EToolProperties : uint8
{
	ETP_Hammering UMETA(DisplayName = "Hammering"),
	ETP_Cutting UMETA(DisplayName = "Cutting"),
	ETP_Digging UMETA(DisplayName = "Digging"),
	ETP_Mining UMETA(DisplayName = "Mining"),
	ETP_Sawing UMETA(DisplayName = "Sawing"),
	ETP_Shearing UMETA(DisplayName = "Shearing"),
};

UENUM(BlueprintType)
enum class EItemQuality : uint8
{
	EIA_None UMETA(DisplayName = "None"),
	EIA_Poor UMETA(DisplayName = "Poor"),
	EIA_Fair UMETA(DisplayName = "Fair"),
	EIA_Good UMETA(DisplayName = "Good"),
	EIA_Excellent UMETA(DisplayName = "Excellent"),
	EIA_Masterwork UMETA(DisplayName = "Masterwork"),
	EIA_Artifact UMETA(DisplayName = "Artifact"),
};

UENUM(BlueprintType)
enum class EWieldableItemType : uint8
{
	EWIT_None UMETA(DisplayName = "None"),
	EWIT_Shield UMETA(DisplayName = "Shield"),
	EWIT_OneHandedWeapon UMETA(DisplayName = "OneHandedWeapon"),
	EWIT_TwoHandedWeapon UMETA(DisplayName = "TwoHandedWeapon"),
	EWIT_Torch UMETA(DisplayName = "LightSource"),
	EWIT_Tank UMETA(DisplayName = "Tank"),
	EWIT_Pistol UMETA(DisplayName = "Pistol"),
	EWIT_Rifle UMETA(DisplayName = "Rifle"),
	EWIT_Tool UMETA(DisplayName = "Tool"),
};

UENUM(BlueprintType)
enum class EFoodType : uint8
{
	EFT_None UMETA(DisplayName = "None"),
	EFT_RawMeat UMETA(DisplayName = "RawMeat"),
	EFT_RawFruit UMETA(DisplayName = "RawFruit"),
	EFT_CookedMeal UMETA(DisplayName = "CookedMeal"),
	EFT_PerservedMeal UMETA(DisplayName = "PerservedMeal"),
};

UENUM(BlueprintType)
enum class EEquipmentLayerType : uint8
{
	EEL_Under UMETA(DisplayName = "Under"),
	EEL_Middle UMETA(DisplayName = "Middle"),
	EEL_Outer UMETA(DisplayName = "Outer")
};

UENUM(BlueprintType)
enum class EArmorClass : uint8
{
	EAC_Clothing UMETA(DisplayName = "Clothing"),
	EAC_Light UMETA(DisplayName = "Light"),
	EAC_Medium UMETA(DisplayName = "Medium"),
	EAC_Heavy UMETA(DisplayName = "Heavy"),
};

