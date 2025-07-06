// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseInterface/BaseWidgetInterface.h"
#include "DialogueData/DialogueDataAsset.h"
#include "ChatWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnContentDisplayed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnded);

// we need to define the ext box here so we can do stuff with it

UCLASS()
class VORPISDIALOGUEMODULE_API UChatWidget : public UUserWidget, public IBaseWidgetInterface
{
	GENERATED_BODY()

public:
	UChatWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable)
	FOnContentDisplayed OnContentDisplayed;
	UPROPERTY(BlueprintAssignable)
	FOnDialogueEnded OnDialogueEnded;

	// timer
	FTimerHandle TimerHandle;
	FTimerDynamicDelegate CheckPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimerRate = 0.08f;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn = true))
	UDialogueDataAsset* DialogueDataAsset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn = true))
	FString FinalChatContent = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn = true))
	FText ShownTextContent = FText::FromString(TEXT(""));
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn = true))
	FString CurrentChatContent = "";
	UFUNCTION(BlueprintCallable)
	FText FStringToFText(FString String) { return FText::FromString(String); };
	UPROPERTY()
	int CurrentChatIndex = 0;

	UFUNCTION(BlueprintCallable)
	void UpdateFinalChatContentLetterByLetter();
	UFUNCTION(BlueprintCallable)
	void UpdateChatContent(FString NewContent);

	UFUNCTION(BlueprintCallable)
	void EndDialogue();

	// interfaces

	virtual void SetContent_Implementation(const FString& Content) override;
	virtual void CloseWidget_Implementation() override;
};
