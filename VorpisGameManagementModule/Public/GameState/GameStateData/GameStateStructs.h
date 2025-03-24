#pragma once

#include "GameState/GameStateData/GameStateEnums.h"
#include "GameStateStructs.generated.h"

USTRUCT(BlueprintType)
struct FPlayerSettingsStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", ClampMax = "100", UIMin = "0", UIMax = "100"))
	int MasterVolume = 60;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", ClampMax = "100", UIMin = "0", UIMax = "100"))
	int MusicVolume = 40;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", ClampMax = "100", UIMin = "0", UIMax = "100"))
	int SFXVolume = 60;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECustomWindowMode WindowMode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EGraphicsSettings GraphicsSettings;

	void IncreaseMasterVolume() { MasterVolume = FMath::Clamp(MasterVolume + 1, 0, 100); }
	void DecreaseMasterVolume() { MasterVolume = FMath::Clamp(MasterVolume - 1, 0, 100); }
	void IncreaseMusicVolume() { MusicVolume = FMath::Clamp(MusicVolume + 1, 0, 100); }
	void DecreaseMusicVolume() { MusicVolume = FMath::Clamp(MusicVolume - 1, 0, 100); }
	void IncreaseSFXVolume() { SFXVolume = FMath::Clamp(SFXVolume + 1, 0, 100); }
	void DecreaseSFXVolume() { SFXVolume = FMath::Clamp(SFXVolume - 1, 0, 100); }
	void SetWindowMode(ECustomWindowMode NewWindowMode) { WindowMode = NewWindowMode; }
	void SetGraphicsSettings(EGraphicsSettings NewGraphicsSettings) { GraphicsSettings = NewGraphicsSettings; }

};