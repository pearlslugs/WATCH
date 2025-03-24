// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogueData.h"
#include "DialogueDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class VORPISDIALOGUEMODULE_API UDialogueDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	FDialogueData DialogueData;
	
};
