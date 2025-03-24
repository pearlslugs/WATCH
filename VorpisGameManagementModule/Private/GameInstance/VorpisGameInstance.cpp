// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/VorpisGameInstance.h"
#include "SaveGameSystem.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFile.h"
#include "HAL/PlatformFilemanager.h"

UVorpisGameInstance::UVorpisGameInstance()
{
	UVorpisGameInstance::FindSaveGameSlotNames();
}

// this finds the save game names so the player can choose which one to load
// you can make a menu with all of the save names to choose from
// you could even load data from each to show the character, their name, their equipment or whatever you want
void UVorpisGameInstance::FindSaveGameSlotNames()
{
	class FFindSavesVisitor : public IPlatformFile::FDirectoryVisitor
	{
	public:
		FFindSavesVisitor() {}
		TArray<FString> SavesFound;

		virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
		{

			if (!bIsDirectory)
			{
				FString FullFilePath(FilenameOrDirectory);
				if (FPaths::GetExtension(FullFilePath) == TEXT("sav"))
				{
					FString CleanFilename = FPaths::GetBaseFilename(FullFilePath);
					CleanFilename = CleanFilename.Replace(TEXT(".sav"), TEXT(""));
					SavesFound.Add(CleanFilename);
				}
			}
			return true;
		}
	};
	TArray<FString> Saves;
	const FString SavesFolder = FPaths::ProjectSavedDir() + TEXT("SaveGames");

	if (!SavesFolder.IsEmpty())
	{
		FFindSavesVisitor Visitor;
		FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*SavesFolder, Visitor);
		Saves = Visitor.SavesFound;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Folder Empty"));
	}
	SaveGameSlotNames.Append(Saves);
}