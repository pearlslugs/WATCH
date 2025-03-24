// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VorpisPlayerController.h"
#include "EnhancedInputComponent.h"
#include "BaseInterface/BaseWidgetInterface.h"
#include "PlayerCharacter/VorpisPlayerCharacterInterface.h"
#include "EnhancedInputSubsystems.h"

AVorpisPlayerController::AVorpisPlayerController()
{

}

void AVorpisPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetControlledActor(GetPawn());
}

void AVorpisPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(ControllerUpAction, ETriggerEvent::Triggered, this, &AVorpisPlayerController::Input_ControllerUp);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent is not found! Make sure Enhanced Input is enabled."));
	}
}

// input
void AVorpisPlayerController::Input_ControllerUp()
{
	if (MountedWidget)
	{
		if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget))
		{
			BaseWidget->WidgetUpInput();
		}
	}
	else if (MountedComponent)
	{
		if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedComponent))
		{
			BaseWidget->WidgetUpInput();
		}
	}
	else if (ControlledActor) {
		if (IVorpisPlayerCharacterInterface* PlayerCharacter = Cast<IVorpisPlayerCharacterInterface>(ControlledActor)) {
			PlayerCharacter->ControllerInputUp();
		}
	}
}
void AVorpisPlayerController::Input_ControllerDown()
{
	if (MountedWidget)
	{
		if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget))
		{
			BaseWidget->WidgetDownInput();
		}
	}
	else if (MountedComponent)
	{
		if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedComponent))
		{
			BaseWidget->WidgetDownInput();
		}
	}
	else if (ControlledActor) {
		if (IVorpisPlayerCharacterInterface* PlayerCharacter = Cast<IVorpisPlayerCharacterInterface>(ControlledActor)) {
			PlayerCharacter->ControllerInputDown();
		}
	}
}
void AVorpisPlayerController::Input_ControllerLeft()
{
	if (MountedWidget)
	{
		if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget))
		{
			BaseWidget->WidgetLeftInput();
		}
	}
	else if (MountedComponent)
	{
		if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedComponent))
		{
			BaseWidget->WidgetLeftInput();
		}
	}
	else if (ControlledActor) {
		if (IVorpisPlayerCharacterInterface* PlayerCharacter = Cast<IVorpisPlayerCharacterInterface>(ControlledActor)) {
			PlayerCharacter->ControllerInputLeft();
		}
	}
}
void AVorpisPlayerController::Input_ControllerRight()
{
	if (MountedWidget)
	{
		if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget))
		{
			BaseWidget->WidgetRightInput();
		}
	}
	else if (MountedComponent)
	{
		if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedComponent))
		{
			BaseWidget->WidgetRightInput();
		}
	}
	else if (ControlledActor) {
		if (IVorpisPlayerCharacterInterface* PlayerCharacter = Cast<IVorpisPlayerCharacterInterface>(ControlledActor)) {
			PlayerCharacter->ControllerInputRight();
		}
	}
}
void AVorpisPlayerController::Input_ControllerSelect()
{
	if (MountedWidget)
	{
		if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget))
		{
			BaseWidget->WidgetSelectInput();
		}
	}
	else if (MountedComponent)
	{
		if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedComponent))
		{
			BaseWidget->WidgetSelectInput();
		}
	}
}
void AVorpisPlayerController::Input_ControllerBack()
{
	if (MountedWidget)
	{
		if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedWidget))
		{
			BaseWidget->WidgetBackInput();
		}
	}
	else if (MountedComponent)
	{
		if (IBaseWidgetInterface* BaseWidget = Cast<IBaseWidgetInterface>(MountedComponent))
		{
			BaseWidget->WidgetBackInput();
		}
	}
}

void AVorpisPlayerController::Input_ControllerStart()
{
	if (ControlledActor) {
		if (IVorpisPlayerCharacterInterface* PlayerCharacter = Cast<IVorpisPlayerCharacterInterface>(ControlledActor)) {
			PlayerCharacter->ControllerInputStart();
		}
	}
}