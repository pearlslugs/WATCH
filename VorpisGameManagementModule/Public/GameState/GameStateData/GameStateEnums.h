#pragma once

#include "GameStateEnums.generated.h"

UENUM(BlueprintType)
enum class EGraphicsSettings : uint8
{
	EGS_Low UMETA(DisplayName = "Low"),
	EGS_Medium UMETA(DisplayName = "Medium"),
	EGS_High UMETA(DisplayName = "High"),
};

UENUM(BlueprintType)
enum class ECustomWindowMode : uint8
{
	ECWT_Windowed UMETA(DisplayName = "Windowed"),
	ECWT_Fullscreen UMETA(DisplayName = "Fullscreen"),
	ECWT_Borderless UMETA(DisplayName = "Borderless"),
};
