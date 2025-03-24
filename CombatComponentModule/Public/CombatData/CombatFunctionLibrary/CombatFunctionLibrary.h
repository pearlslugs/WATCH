#pragma once

#include "CombatData/CombatStructs.h"
#include "CombatFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FAttackBuilderStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Builder")
	FAttackStruct AttackStruct; // defines the attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Builder")
	TMap<EPhysicalDamageType, int> DamageMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Builder")
	float Velocity; // build with strength and weapon weight
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Builder")
	float Precision; // build with dex and weapon type
	
};

USTRUCT(BlueprintType)
struct FAttackFunctions
{
	GENERATED_BODY()
	/// <Attack builder>
	/// so what does this do?
	/// I am not sure, we wil figure out laterh
	/// </Attack builder>
};

USTRUCT(BlueprintType)
struct FDefenseFunctions
{
	GENERATED_BODY()
};