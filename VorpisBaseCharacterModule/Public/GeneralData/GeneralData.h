#pragma once

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
struct FGeneralUtils
{
	GENERATED_BODY()
public:
	static FVector ClampVector(FVector VectorToClamp, float MinValue, float MaxValue)
	{
		FVector ClampedVector = FVector(FMath::Clamp(VectorToClamp.X, MinValue, MaxValue), FMath::Clamp(VectorToClamp.Y, MinValue, MaxValue), FMath::Clamp(VectorToClamp.Z, MinValue, MaxValue));
		return ClampedVector;
	}
};