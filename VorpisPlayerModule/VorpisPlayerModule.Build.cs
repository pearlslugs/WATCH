// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VorpisPlayerModule : ModuleRules
{
	public VorpisPlayerModule (ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
            "VorpisBaseCharacterModule",
				"ALS",
            "VorpisDialogueModule",
            "VorpisLockOnModule",
            "VorpisInputBufferModule",
            "VorpisEquipmentModule",
            "VorpisInteractableModule",
            "VorpisCharacterInterfaceModule",
            "CombatComponentModule",
            "EnhancedInput",
				"MontageManagerModule",
            "VorpisCharacterStateModule",
            "VorpisDialogueModule",
            "VorpisWeaponCollisionModule",
            "VorpisItemsModule",
            "VorpisControllers",
				"UMG",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"UMG",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
