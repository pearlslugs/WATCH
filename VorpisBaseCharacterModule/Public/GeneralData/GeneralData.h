#pragma once

#include "StatsData/StatusStats/StatusEnums.h"
#include "ItemData/ItemEnums.h"
#include "ItemData/WeaponData/WeaponEnums.h"
#include "GeneralData.generated.h"

UENUM(BlueprintType)
enum class EStrafingMovementDirection : uint8
{
	ESMD_Forward UMETA(DisplayName = "Forward"),
	ESMD_Backward UMETA(DisplayName = "Backward"),
	ESMD_Left UMETA(DisplayName = "Left"),
	ESMD_Right UMETA(DisplayName = "Right"),
};

USTRUCT(BlueprintType)
struct FCoalatedProtectionMap
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EPhysicalDamageType, int> ProtectionMap;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Coverage;
	void InitializeMap() {
		ProtectionMap.Add(EPhysicalDamageType::EPDT_Blunt, 0);
		ProtectionMap.Add(EPhysicalDamageType::EPDT_Composure, 0);
		ProtectionMap.Add(EPhysicalDamageType::EPDT_Hack, 0);
		ProtectionMap.Add(EPhysicalDamageType::EPDT_Pierce, 0);
		ProtectionMap.Add(EPhysicalDamageType::EPDT_Slash, 0);
	};
};

USTRUCT(BlueprintType)
struct FGeneralUtils
{
	GENERATED_BODY()
public:
	static FVector ClampVector(FVector VectorToClamp, float MinValue, float MaxValue)
	{
		FVector ClampedVector = FVector(FMath::Clamp(VectorToClamp.X, MinValue, MaxValue), FMath::Clamp(VectorToClamp.Y, MinValue, MaxValue), FMath::Clamp(VectorToClamp.Z, MinValue, MaxValue));
		return ClampedVector;
	}
	static bool IsLeftSide(FString String)
	{
		return String.Contains("_l");
	}

	static bool IsFinger(FString String)
	{
		return String.Contains("pinky", ESearchCase::IgnoreCase) || String.Contains("thumb", ESearchCase::IgnoreCase) ||
			String.Contains("ring", ESearchCase::IgnoreCase) || String.Contains("Middle", ESearchCase::IgnoreCase) ||
			String.Contains("Index", ESearchCase::IgnoreCase);
	}

	static EBodyPart BoneToBodyPart(FName HitBoneName)
	{
		FString BoneString = HitBoneName.ToString();
		if (BoneString.Contains("calf", ESearchCase::IgnoreCase) || BoneString.Contains("thigh", ESearchCase::IgnoreCase) ||
			BoneString.Contains("foot", ESearchCase::IgnoreCase)) {
			if (IsLeftSide(BoneString)) {
				return EBodyPart::EBP_LeftLeg;
			}
			else {
				return EBodyPart::EBP_RightLeg;
			}
		}
		if (BoneString.Contains("spine", ESearchCase::IgnoreCase) || BoneString.Contains("clavicle", ESearchCase::IgnoreCase) ||
			BoneString.Contains("pelvis", ESearchCase::IgnoreCase)) {
			return EBodyPart::EBP_Torso;
		}
		if (BoneString.Contains("head", ESearchCase::IgnoreCase)) {
			return EBodyPart::EBP_Head;
		}
		if (BoneString.Contains("neck", ESearchCase::IgnoreCase)) {
			return EBodyPart::EBP_Neck;
		}
		if (BoneString.Contains("hand", ESearchCase::IgnoreCase) || BoneString.Contains("arm", ESearchCase::IgnoreCase) || IsFinger(BoneString)) {
			if (IsLeftSide(BoneString)) {
				return EBodyPart::EBP_LeftArm;
			}
			else {
				return EBodyPart::EBP_RightArm;
			}
		}
		return EBodyPart::EBP_MAX;
	}

	static TArray<EEquipmentSlot> BodyPartToEquipmentSlot(EBodyPart BodyPart)
	{
		TArray<EEquipmentSlot> RelavantSlots;
		switch (BodyPart)
		{
		case EBodyPart::EBP_Head:
			RelavantSlots.Add(EEquipmentSlot::EES_Head);
			break;
		case EBodyPart::EBP_LeftArm:
		case EBodyPart::EBP_RightArm:
			
			RelavantSlots.Add(EEquipmentSlot::EES_Arms);
			break;
		case EBodyPart::EBP_LeftLeg:
		case EBodyPart::EBP_RightLeg:
			EEquipmentSlot::EES_Legs;
			break;
		case EBodyPart::EBP_Torso:
			EEquipmentSlot::EES_UpperBody;
			break;
		case EBodyPart::EBP_Neck:
			EEquipmentSlot::EES_Neck;
			break;
		}
		return RelavantSlots;
	}
	static TArray<EBodyPart> EquipmentSlotToBodyPart(EEquipmentSlot Slot)
	{
		TArray<EBodyPart> BodyParts;
		switch (Slot) {
		case EEquipmentSlot::EES_Head:
			BodyParts.Add(EBodyPart::EBP_Head);
			break;
		case EEquipmentSlot::EES_Hands:
		case EEquipmentSlot::EES_Arms:
			BodyParts.Add(EBodyPart::EBP_RightArm);
			BodyParts.Add(EBodyPart::EBP_LeftArm);
			break;
		case EEquipmentSlot::EES_Shoulders:
		case EEquipmentSlot::EES_UpperBody:
			BodyParts.Add(EBodyPart::EBP_Torso);
			break;
		case EEquipmentSlot::EES_Legs:
		case EEquipmentSlot::EES_Feet:
			BodyParts.Add(EBodyPart::EBP_LeftLeg);
			BodyParts.Add(EBodyPart::EBP_RightLeg);
			break;
		case EEquipmentSlot::EES_Neck:
			BodyParts.Add(EBodyPart::EBP_Neck);
		}
		return BodyParts;
	}

	static int GetTotalDamageFromAttack(TMap<EPhysicalDamageType, int> DamageMap, TMap<EPhysicalDamageType, int> ProtectionMap, EPhysicalDamageType PrimaryDamage)
	{
		int TotalDamage = 0;
		TotalDamage += (ProtectionMap[EPhysicalDamageType::EPDT_Blunt] - DamageMap[EPhysicalDamageType::EPDT_Blunt]);
		TotalDamage += (ProtectionMap[PrimaryDamage] - DamageMap[PrimaryDamage]);
		return TotalDamage;
	}
	static TMap<EPhysicalDamageType, int> CollateProtectionMaps(TMap<EPhysicalDamageType, int> ExistingMap, TMap<EPhysicalDamageType, int> AdditionalMap)
	{
		TMap<EPhysicalDamageType, int> NewMap;
		NewMap.Add(EPhysicalDamageType::EPDT_Blunt,
			(
			ExistingMap[EPhysicalDamageType::EPDT_Blunt] + 
			AdditionalMap[EPhysicalDamageType::EPDT_Blunt]
			));
		NewMap.Add(EPhysicalDamageType::EPDT_Hack,
			(
			ExistingMap[EPhysicalDamageType::EPDT_Hack] + 
			AdditionalMap[EPhysicalDamageType::EPDT_Hack]
			));
		NewMap.Add(EPhysicalDamageType::EPDT_Pierce,
			(
			ExistingMap[EPhysicalDamageType::EPDT_Pierce] +
			AdditionalMap[EPhysicalDamageType::EPDT_Pierce]
			));
		NewMap.Add(EPhysicalDamageType::EPDT_Slash,
			(
			ExistingMap[EPhysicalDamageType::EPDT_Slash] + 
			AdditionalMap[EPhysicalDamageType::EPDT_Slash]
			));
		return NewMap;
	}
};