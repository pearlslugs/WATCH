#pragma once

#include "ItemEnums.h"
#include "WeaponData/WeaponEnums.h"
#include "DataAsset/ItemDataAsset.h"
#include "ItemStructs.generated.h"


USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()
public:
	// basic data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basics")
	FName ItemName; // quality + material + name, so like "exeptional bronze sword"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basics")
	FGuid ItemGuid; // how we sort it in  inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basics")
	int Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basics")
	bool IsFull;
	
	// damage data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool IsWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TMap<EPhysicalDamageType, int> AdjustedDamageMap; // apply scaling and quality to base damage

	// armor data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
	bool IsArmor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
	TMap<EPhysicalDamageType, int> ProtectionMap; // adjusted protection from quality and condition
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
	int Coverage;
	
	// other data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	int Condition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	EItemQuality ItemQuality;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material")
	EMaterialType MaterialType;

	// mesh data
	// when its created, we pick a mesh index from the arrays
	// this class is saved, so when its reinitialized, we can get the same mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	int BaseMeshIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	int BladeMeshIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	int SkeletalMeshIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeneralItem")
	UItemDataAsset* ItemAsset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeneralItem")
	FGuid InitialItemGuid; // for look up i guess

	// tasks
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tasks")
	TMap<ETaskType, bool> CompletedTasksMap;

};

USTRUCT(BlueprintType)
struct FPickUpData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	FItemData ItemData = FItemData();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	FVector Location = FVector();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Active = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DroppedInToWorld = false;
};

USTRUCT(BlueprintType)
struct FToolCompareType {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Success;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ErrorMessages;
};