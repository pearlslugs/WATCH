#pragma once

#include "CombatData/CombatEnums.h"
#include "ItemData/WeaponData/WeaponEnums.h"
#include "CombatStructs.generated.h"

USTRUCT(BlueprintType)
struct FInitialAttackData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECombatPosition Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Multiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Blockable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPhysicalDamageType PrimaryDamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ComboCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponSwingType SwingType;
};

USTRUCT(BlueprintType)
struct FAttackStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInitialAttackData InitialAttackData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Velocity = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Precision = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EPhysicalDamageType, int> DamageMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName HitBone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector HitLocation;
};

USTRUCT(BlueprintType)
struct FHitTraceResults
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackTrace")
	FName HitBone = "None";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackTrace")
	FVector HitLocation = FVector();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackTrace")
	FVector AttackerLocation = FVector();
};

USTRUCT(BlueprintType)
struct FFinishedAttackStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FHitTraceResults HitTraceResults;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAttackStruct AttackData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPhysicalDamageType PrimaryDamageType;
};