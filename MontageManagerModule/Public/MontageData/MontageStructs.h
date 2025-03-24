#pragma once

#include "Animation/AnimMontage.h"
#include "CombatData/CombatEnums.h"
#include "MontageStructs.generated.h"

USTRUCT(BlueprintType)
struct FMontageArray
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TArray<UAnimMontage*> Montages;
};

USTRUCT(BlueprintType)
struct FDirectionalMontages
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TMap<ECombatPosition, FMontageArray> Montages;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TMap<ECombatPosition, FMontageArray> AlternativeMontages;
};