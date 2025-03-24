#pragma once

#include "CharacterStateEnums.generated.h"

UENUM(BlueprintType)
enum class EGeneralState : uint8
{
	EGS_None UMETA(DisplayName = "None"),
	EGS_Combat UMETA(DisplayName = "Combat"),
	EGS_InConversation UMETA(DisplayName = "InConversation"),
	EGS_FixingEquipment UMETA(DisplayName = "FixingEquipment"),
	EGS_Disabled UMETA(DisplayName = "Disabled"),
	EGS_Dead UMETA(DisplayName = "Dead"),
};

UENUM(BlueprintType)
enum class ECombatState : uint8
{
	ECS_None UMETA(DisplayName = "None"),
	ECS_Attacking UMETA(DisplayName = "Attacking"),
	ECS_PreparingAttack UMETA(DisplayName = "PreparingAttack"),
	ECS_ShieldBlocking UMETA(DisplayName = "ShieldBlocking"),
	ECS_Dodging UMETA(DisplayName = "Dodging"),
	ECS_Aiming UMETA(DisplayName = "Aiming"),
	ECS_Reloading UMETA(DisplayName = "Reloading"),
	ECS_Throwing UMETA(DisplayName = "Throwing"),
	ECS_Kicking UMETA(DisplayName = "Kicking"),
	ECS_Parrying UMETA(DisplayName = "Parrying"),
	EGS_HitStunned UMETA(DisplayName = "HitStunned"),
	EGS_BlockStunned UMETA(DisplayName = "BlockStunned"),
};

UENUM(BlueprintType)
enum class ECharacterPersonality : uint8
{
	ECP_None UMETA(DisplayName = "None"),
	ECP_Hostile UMETA(DisplayName = "Hostile"),
	ECP_Reasonable UMETA(DisplayName = "Reasonable"),
	ECP_Desperate UMETA(DisplayName = "Desperate"),
	ECP_Scared UMETA(DisplayName = "Scared"),
};

UENUM(BlueprintType)
enum class EAiMainBehavior : uint8
{
	AMB_Fighting UMETA(DisplayName = "Fighting"),				    // 0
	AMB_Fleeing UMETA(DisplayName = "Fleeing"),					    // 1
	AMB_Hiding UMETA(DisplayName = "Hiding"),					       // 2
	AMB_Surrendering UMETA(DisplayName = "Surrendering"),			 // 3
	AMB_Manipulating UMETA(DisplayName = "Manipulating"),			 // 4
};

UENUM(BlueprintType)
enum class EAiCombatState : uint8
{
	EACS_None UMETA(DisplayName = "None"),							    // 0
	EACS_StartAttacking UMETA(DisplayName = "StartAttacking"),   // 1
	EACS_Attacking UMETA(DisplayName = "Attacking"),			    // 2	
	EACS_StartStrafing UMETA(DisplayName = "StartStrafing"),		 // 3
	EACS_Strafing UMETA(DisplayName = "Strafing"),				    // 4
	EACS_Dodging UMETA(DisplayName = "Dodging"),					    // 5
	EACS_FollowingTarget UMETA(DisplayName = "FollowingTarget"), // 6
	EACS_HitStunned UMETA(DisplayName = "HitStunned"),				 // 7
	EACS_BlockStunned UMETA(DisplayName = "BlockStunned"),		 // 8
};