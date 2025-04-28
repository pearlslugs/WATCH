// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VorpisBaseCharacterModule : ModuleRules
{
	public VorpisBaseCharacterModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
         "Core",
         "CoreUObject",
         "Engine",
         "InputCore",
         "EnhancedInput",
         "AIModule",
         "ALS",
         "ALSCamera", 
         "VorpisCharacterInterfaceModule",
         "VorpisWeaponCollisionModule",
         "CombatComponentModule",
         "VorpisItemsModule",
         "VorpisCharacterStateModule",
         "VorpisEquipmentModule",
         "VorpisInteractableModule",
         "MontageManagerModule",
         "Niagara",
         "VorpisStatsModule"
      });

        PrivateDependencyModuleNames.AddRange(new[]
        {
            "EnhancedInput",
            "Niagara",

        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
