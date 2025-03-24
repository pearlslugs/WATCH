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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
	FName HitBone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
	FVector HitLocation;
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
};