// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ChatWidget.h"

UChatWidget::UChatWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set the default values for the chat widget
	CurrentChatIndex = 0;
	CurrentChatContent = "";
}

void UChatWidget::UpdateFinalChatContentLetterByLetter()
{
	if (CurrentChatContent.Equals(FinalChatContent))
	{
		return;
	}
	else {
		CurrentChatIndex++;
		CurrentChatContent = FinalChatContent.Left(CurrentChatIndex);
		ShownTextContent = FStringToFText(CurrentChatContent);
		// set timer
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UChatWidget::UpdateFinalChatContentLetterByLetter, TimerRate, false);
	}
}

void UChatWidget::SetContent(FString Content)
{
	UpdateChatContent(Content);
}

void UChatWidget::UpdateChatContent(FString NewChatContent)
{
	FinalChatContent = NewChatContent;
	CurrentChatIndex = 0;
	CurrentChatContent = "";
	UpdateFinalChatContentLetterByLetter();
}

void UChatWidget::CloseWidget() 
{
	UChatWidget::EndDialogue();
};

void UChatWidget::EndDialogue()
{
	OnDialogueEnded.Broadcast();
	RemoveFromParent();
}