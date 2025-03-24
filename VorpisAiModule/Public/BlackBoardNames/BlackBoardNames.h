#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

namespace BBKeys
{
	TCHAR const* const TargetedEnemy = TEXT("TargetedEnemy");
	TCHAR const* const EnemyLocation = TEXT("EnemyLocation");
	TCHAR const* const IsDead = TEXT("IsDead");
	TCHAR const* const AIGeneralState = TEXT("AIGeneralState");
	TCHAR const* const StrafingDirection = TEXT("StrafingDirection");
	TCHAR const* const PitchRotation = TEXT("PitchRotation");
	TCHAR const* const DisableDescisionMaker = TEXT("PitchRotation");
	TCHAR const* const IsInAttackRange = TEXT("IsInAttackRange");
	TCHAR const* const IsDisabled = TEXT("IsDisabled");
	TCHAR const* const Distance = TEXT("Distance");
	TCHAR const* const YawAngle = TEXT("YawAngle");
	TCHAR const* const AiDecision = TEXT("AiDecision");
	TCHAR const* const TeamName = TEXT("TeamName");
	TCHAR const* const Aggression = TEXT("Aggression");
	TCHAR const* const FollowingPath = TEXT("FollowingPath");
	TCHAR const* const Leader = TEXT("Leader");
	TCHAR const* const Target = TEXT("Target");
	TCHAR const* const Personality = TEXT("Personality");
	TCHAR const* const AiCombatState = TEXT("CombatState");
	TCHAR const* const InDialogue = TEXT("InDialogue");
	TCHAR const* const AiMainBehavior = TEXT("AiMainBehavior");
	TCHAR const* const TargetAknowledged = TEXT("TargetAknowledged");
	TCHAR const* const HitCounter = TEXT("HitCounter");
	TCHAR const* const MaxHitCounter = TEXT("MaxHitCounter");
	TCHAR const* const StrafeTime = TEXT("StrafeTime");
	TCHAR const* const MaxStrafeTime = TEXT("MaxStrafeTime");
	TCHAR const* const OnAtackCoolDown = TEXT("OnAtackCoolDown");
	TCHAR const* const OnStrafeCoolDown = TEXT("OnStrafeCoolDown");
}