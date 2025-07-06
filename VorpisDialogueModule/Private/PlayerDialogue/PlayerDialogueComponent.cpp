// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDialogue/PlayerDialogueComponent.h"
#include "BaseInterface/BaseWidgetInterface.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UPlayerDialogueComponent::UPlayerDialogueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerDialogueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerDialogueComponent::GoToNextDialogueOption(FGuid Guid)
{
	if (!MountedWidget || !DialogueDataAsset) { return; }
	IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget);
	if (!BaseWidget) { return; }
	if (Guid == FGuid()) 
	{
		TArray< FDialogueStrings> DialogueOptions;
		DialogueDataAsset->DialogueData.DialogueMap.GenerateValueArray(DialogueOptions);
		if (DialogueOptions.Num() > 0 && DialogueOptions.Num() > CurrentDialogueOptionIndex)
		{
			// we wont eally need the dialogue text to be an aray, we can chop it up later. just use 0 for now
			IBaseWidgetInterface::Execute_SetContent(MountedWidget, DialogueOptions[CurrentDialogueOptionIndex].DialogueText[0]);
			CurrentDialogueOptionIndex++;
			return;
		}
	}
	else 
	{
		TArray<FString> DialogueText = DialogueDataAsset->DialogueData.DialogueMap[Guid].DialogueText;
		if (DialogueText.Num() > 0) 
		{
			IBaseWidgetInterface::Execute_SetContent(MountedWidget, DialogueText[0]);
			return;
		}
	}
	UPlayerDialogueComponent::EndDialogue();
	OnDialogueEnd.Broadcast();
}

void UPlayerDialogueComponent::SetMountedWidget(UUserWidget* Widget)
{
	MountedWidget = Widget;
	UPlayerDialogueComponent::GoToNextDialogueOption(CurrentDialogueOptionId);
}

void UPlayerDialogueComponent::EndDialogue()
{
	if (MountedWidget) 
	{
		IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget);
		if (BaseWidget) { 
			IBaseWidgetInterface::Execute_CloseWidget(MountedWidget);
		}
		else { MountedWidget->RemoveFromParent(); }
		MountedWidget = nullptr;
	}
	OnDialogueEnd.Broadcast();
}

void UPlayerDialogueComponent::WidgetSelectInput_Implementation()
{
	// before we go to next dialogue option, we need to check if we have reached the end of the dialogue
	if (!MountedWidget || !DialogueDataAsset) { return; }
	IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget);
	if (!BaseWidget) { return; }
	TArray< FDialogueStrings> DialogueOptions;
	DialogueDataAsset->DialogueData.DialogueMap.GenerateValueArray(DialogueOptions);
	if (DialogueOptions.Num() > 0) 
	{
		if (CurrentDialogueOptionIndex >= DialogueOptions.Num()) 
		{
			UPlayerDialogueComponent::EndDialogue();
		}
		else 
		{
			UPlayerDialogueComponent::GoToNextDialogueOption(DialogueOptions[CurrentDialogueOptionIndex].DialogueId);
		}
	}
	else 
	{
		UPlayerDialogueComponent::EndDialogue();
	}	
}

void UPlayerDialogueComponent::WidgetUpInput_Implementation() { if (MountedWidget) { if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget)) {	BaseWidget->WidgetUpInput(); }}}
void UPlayerDialogueComponent::WidgetDownInput_Implementation() { if (MountedWidget) { if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget)) { BaseWidget->WidgetDownInput(); }}}
void UPlayerDialogueComponent::WidgetLeftInput_Implementation() {	if (MountedWidget) {	if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget)) {	BaseWidget->WidgetLeftInput(); }}}
void UPlayerDialogueComponent::WidgetRightInput_Implementation() { if (MountedWidget) { if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget)) { BaseWidget->WidgetRightInput(); }}}
void UPlayerDialogueComponent::WidgetBackInput_Implementation() { if (MountedWidget) { if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget)) { BaseWidget->WidgetBackInput(); }}}