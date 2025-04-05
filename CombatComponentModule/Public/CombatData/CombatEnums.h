#pragma once

#include "CombatEnums.generated.h"

UENUM(BlueprintType)
enum class ECombatPosition : uint8
{
	ECP_High UMETA(DisplayName = "High"),
	ECP_Left UMETA(DisplayName = "Left"),
	ECP_Right UMETA(DisplayName = "Right"),
	ECP_Low UMETA(DisplayName = "Low"),
	ECP_None UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class EDodgeDirection : uint8
{
	ESMD_Forward UMETA(DisplayName = "Forward"),
	ESMD_Backward UMETA(DisplayName = "Backward"),
	ESMD_Left UMETA(DisplayName = "Left"),
	ESMD_Right UMETA(DisplayName = "Right"),
};