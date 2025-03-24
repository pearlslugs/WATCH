#pragma once

#include "DialogueData.generated.h"

UENUM(BlueprintType)
enum class EDialogueOutcome : uint8
{
	EDO_None UMETA(DisplayName = "None"),
	EDO_Hostility UMETA(DisplayName = "Hostility"),
	EDO_Surrender UMETA(DisplayName = "Surrender"),
	EDO_Flee UMETA(DisplayName = "Flee"),
	EDO_PlayerSurrenders UMETA(DisplayName = "PlayerSurrenders"),
};

USTRUCT(BlueprintType)
struct FDialogueStrings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid DialogueId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> DialogueText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid NextDialogueId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDialogueOutcome Outcome;
};

USTRUCT(BlueprintType)
struct FDialogAnswers
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGuid, FString> Answers; // guids go to next dialogue
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDialogueOutcome Outcome;
};

USTRUCT(BlueprintType)
struct FDialogueWithChoices
{
	GENERATED_BODY();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid DialogueId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DialogueText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDialogAnswers DialogueAnswers;
};

USTRUCT(BlueprintType)
struct FDialogueData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGuid, FDialogueStrings> DialogueMap; // some ending dialogues will point to a dialogue with questions
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGuid, FDialogueWithChoices> DialogueWithChoicesMap; // dialogues with chouces answers point back to other dialogues

};