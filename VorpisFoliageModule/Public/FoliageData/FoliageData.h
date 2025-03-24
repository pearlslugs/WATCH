#pragma once

#include "FoliageData.generated.h"

UENUM(BlueprintType)
enum class EFoliageType : uint8
{
	EFT_TallTree UMETA(DisplayName = "TallTree"),
	EFT_ScythTree UMETA(DisplayName = "ScythTree"),
	EFT_Grass UMETA(DisplayName = "Grass"),
	EFT_Flower UMETA(DisplayName = "Flower"),
	EFT_EyeBush UMETA(DisplayName = "EyeBush"),
	EFT_WormBush UMETA(DisplayName = "WormBush"),
};

USTRUCT(BlueprintType)
struct FFoliageMap
{
	GENERATED_BODY()
public:
	//@Info: FoliageMap: A Map of FoliageType and the amount to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EFoliageType, int> FoliageMap;
};
