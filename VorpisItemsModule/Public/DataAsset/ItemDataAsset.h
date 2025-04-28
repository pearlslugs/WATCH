// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "ItemData/WeaponData/WeaponEnums.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "ItemData/ItemEnums.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class VORPISITEMSMODULE_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	// basic data
	UItemDataAsset();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basics")
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basics")
	FGuid AssetGuid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basics")
	UTexture2D* IconTexture;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basics")
	bool IsStackable;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basics")
	int MaxStackSize;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basics")
	FString ItemDescription;

	// mesh data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TArray<UStaticMesh*> BaseMeshes; // either the whole mesh or its the hilt of a weapon
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TArray<UStaticMesh*> BladeMeshes; // only for weapons
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TArray<USkeletalMesh*> SkeletalMeshes; // armor or unique items 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	bool UseSkeletalMesh;

	// equipment data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip")
	EEquipmentSlot EquipmentSlot;
	
	// socket data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Socket")
	EEquipSocketOption EquipSocketOption;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Socket")
	EUnequipSocketOption UnequipSocketOption;

	// weildable data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weildable")
	bool IsWeildable;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weildable")
	bool IsTwoHanded;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weildable")
	EWieldableItemType WieldableItemType;

	// damage data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	TMap<EPhysicalDamageType, int> DamageMap;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	FGuid StatsScalingGuid; // we dont want all the modules to rely on each other
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	//	EWST_Slash UMETA(DisplayName = "Swing"),		0
	//	EWST_Thrust UMETA(DisplayName = "Thrust"),	1
	//	EWST_Bash UMETA(DisplayName = "Bash"),			2
	TMap<uint8, EPhysicalDamageType>  SwingDamageTypeMap;

	// food data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Food")
	bool IsFood;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Food")
	EFoodType FoodType;

	// consumable data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consumable")
	bool IsConsumable;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consumable")
	EConsumableType ConsumableType;

	// wearable data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wearable")
	bool IsWearable;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wearable")
	EEquipmentLayerType EquipmentLayerType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wearable")
	TMap<EPhysicalDamageType, int> ProtectionMap;

	// inventory data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int ItemHeight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int ItemWidth;

	// armor data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor")
	EArmorClass ArmorClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor")
	int Coverage;


	FName GetEquipSocketName() {
		switch (EquipSocketOption)
		{
			case EEquipSocketOption::ESO_LeftHandOneHandedSlot:
				return FName("LeftHandOneHandedSlot");
				break;
			case EEquipSocketOption::EESO_OneHandedWeaponSocket:
				return FName("OneHandedWeaponSocket");
				break;
			case EEquipSocketOption::EESO_TwoHandedBaseGripSocket:
				return FName("TwoHandedBaseGripSocket");
				break;
			case EEquipSocketOption::EESO_TwoHandedPoleGripSocket:
				return FName("TwoHandedPoleGripSocket");
				break;
		}
		return FName("null");
	}

	FName GetUnequipSocketName()
	{
			switch (UnequipSocketOption)
		{
				case EUnequipSocketOption::EUS_HipSocket:
					return FName("HipSocket");
					break;
				case EUnequipSocketOption::EUS_BackSocket:
					return FName("BackSocket");
					break;
				case EUnequipSocketOption::EUS_BeltSocket:
					return FName("BeltSocket");
					break;
		}
			return FName("null");
	}

};
