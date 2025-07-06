#pragma once

#include "CharacterStateEnums.generated.h"

// idk what i was thinking, we need to consolidate ai 
// combat state and combat state and then make the set combat state function update the blackboard

// stupid lmao

UENUM(BlueprintType)
enum class EGeneralState : uint8
{
	EGS_None UMETA(DisplayName = "None"),
	EGS_Combat UMETA(DisplayName = "Combat"),
	EGS_InConversation UMETA(DisplayName = "InConversation"),
	EGS_IKTask UMETA(DisplayName = "IKTask"),
	EGS_NonIKTask UMETA(DisplayName = "NonIkTask"),
	EGS_Disabled UMETA(DisplayName = "Disabled"),
	EGS_Dead UMETA(DisplayName = "Dead"),
};

UENUM(BlueprintType)
enum class ETaskState : uint8
{
	ETS_None UMETA(DisplayName =  "None"),
	ETS_HarvestFuelPlant UMETA(DisplayName = "HarvestFuelPlant"),
};

UENUM(BlueprintType)
enum class ECombatState : uint8
{
	ECS_None UMETA(DisplayName = "None"),									// 0
	ECS_StartAttacking UMETA(DisplayName = "StartAttacking"),		// 1
	ECS_Attacking UMETA(DisplayName = "Attacking"),						// 2
	ECS_ShieldBlocking UMETA(DisplayName = "ShieldBlocking"),		// 3
	ECS_Dodging UMETA(DisplayName = "Dodging"),							// 4
	ECS_Aiming UMETA(DisplayName = "Aiming"),								// 5
	ECS_Reloading UMETA(DisplayName = "Reloading"),						// 6
	ECS_Throwing UMETA(DisplayName = "Throwing"),						// 7
	ECS_Kicking UMETA(DisplayName = "Kicking"),							// 8
	ECS_Parrying UMETA(DisplayName = "Parrying"),						// 9
	ECS_HitStunned UMETA(DisplayName = "HitStunned"),					// 10
	ECS_BlockStunned UMETA(DisplayName = "BlockStunned"),				// 11
	ECS_StartStrafing UMETA(DisplayName = "StartStrafing"),			// 12
	ECS_Strafing UMETA(DisplayName = "Strafing"),						// 13
	EACS_FollowingTarget UMETA(DisplayName = "FollowingTarget"),	// 14
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