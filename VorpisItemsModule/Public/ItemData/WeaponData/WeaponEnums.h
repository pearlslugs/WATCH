#pragma once

#include "WeaponEnums.generated.h"

UENUM(BlueprintType)
enum class EPhysicalDamageType : uint8
{
	EPDT_None UMETA(DisplayName = "None"),
	EPDT_Blunt UMETA(DisplayName = "Blunt"),
	EPDT_Hack UMETA(DisplayName = "Hack"),
	EPDT_Slash UMETA(DisplayName = "slash"),
	EPDT_Pierce UMETA(DisplayName = "Pierce"),
	EPDT_Composure  UMETA(DisplayName = "Composure")
};