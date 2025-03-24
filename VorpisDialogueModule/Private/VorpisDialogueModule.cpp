// Copyright Epic Games, Inc. All Rights Reserved.

#include "VorpisDialogueModule.h"

#define LOCTEXT_NAMESPACE "FVorpisDialogueModule"

void FVorpisDialogueModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FVorpisDialogueModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVorpisDialogueModule, VorpisDialogueModule)