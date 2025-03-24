// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class WATCHEditorTarget : TargetRules
{
	public WATCHEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("WATCH");
      ExtraModuleNames.Add("VorpisBaseCharacterModule");
      ExtraModuleNames.Add("VorpisItemsModule");
      ExtraModuleNames.Add("VorpisInteractableModule");
      ExtraModuleNames.Add("VorpisGameManagementModule");
      ExtraModuleNames.Add("CombatComponentModule");
      ExtraModuleNames.Add("VorpisWeaponCollisionModule");
      ExtraModuleNames.Add("VorpisCharacterInterfaceModule");
      ExtraModuleNames.Add("VorpisPlayerModule");
      ExtraModuleNames.Add("VorpisNPCModule");
      ExtraModuleNames.Add("VorpisInputBufferModule");
      ExtraModuleNames.Add("VorpisLockOnModule");
      ExtraModuleNames.Add("VorpisEquipmentModule");
      ExtraModuleNames.Add("WatchPlayerController");
      ExtraModuleNames.Add("MontageManagerModule");
      ExtraModuleNames.Add("VorpisFoliageModule");
      ExtraModuleNames.Add("VorpisControllers");
      ExtraModuleNames.Add("VorpisAiModule");
      ExtraModuleNames.Add("VorpisDialogueModule");
      ExtraModuleNames.Add("VorpisWidgetInterfaceModule");
   }
}
