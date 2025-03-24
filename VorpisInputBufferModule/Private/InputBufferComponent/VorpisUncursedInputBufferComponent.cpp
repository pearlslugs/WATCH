// Fill out your copyright notice in the Description page of Project Settings.

#include "InputBufferComponent/VorpisUncursedInputBufferComponent.h"
#include "InputBufferData/InputBufferEnums.h"


// Sets default values for this component's properties
UVorpisUncursedInputBufferComponent::UVorpisUncursedInputBufferComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	IsBufferOpen = true;
	CanChangeKey = true;

	// ...
}


// Called when the game starts
void UVorpisUncursedInputBufferComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UVorpisUncursedInputBufferComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UVorpisUncursedInputBufferComponent::AcceptKey(EBufferKey InKey)
{

	if (bResetBuffer)
	{
		CurrentKey = InKey;
		bResetBuffer = false;
		UVorpisUncursedInputBufferComponent::ConsumeBuffer();
	}
	if (IsBufferOpen)
	{
		// store the key for the next use, if the player is already in the middle of doing something, like attacking
		// we will save the key, but not consume. an anim notify at the end of the aniamtion will then consume the current key
		CurrentKey = InKey;
		if (CanChangeKey)
		{
			CanChangeKey = false;
			bResetBuffer = false;
			UVorpisUncursedInputBufferComponent::ConsumeBuffer();
		}

	}
	else if (GetIsHighPriorityInput(InKey) || bResetBuffer)
	{
		IsBufferOpen = true;
		AcceptKey(InKey);
	}
}


void UVorpisUncursedInputBufferComponent::OpenBuffer()
{
	CurrentKey = EBufferKey::EBK_None;
	IsBufferOpen = true;
	CanChangeKey = false;
}
void UVorpisUncursedInputBufferComponent::CloseBuffer()
{
	IsBufferOpen = false;
}
void UVorpisUncursedInputBufferComponent::ConsumeBuffer()
{
	if (CurrentKey != EBufferKey::EBK_None)
	{
		OnBufferConsumed.Broadcast(CurrentKey);
	}
	UVorpisUncursedInputBufferComponent::ClearBuffer();
}
void UVorpisUncursedInputBufferComponent::ClearBuffer()
{
	CurrentKey = EBufferKey::EBK_None;
	IsBufferOpen = true;
	CanChangeKey = true;
}

void UVorpisUncursedInputBufferComponent::PreventEarlyInput()
{
	IsBufferOpen = false;
}

bool UVorpisUncursedInputBufferComponent::CompareKeys(EBufferKey IncomingKey)
{
	if (UVorpisUncursedInputBufferComponent::GetIsHighPriorityInput(IncomingKey))
	{
		return true;
	}
	else if (UVorpisUncursedInputBufferComponent::GetIsHighPriorityInput(CurrentKey))
	{
		return false;
	}
	return true;
}

bool UVorpisUncursedInputBufferComponent::GetIsHighPriorityInput(EBufferKey IncomingKey)
{
	if (IncomingKey == EBufferKey::EBK_Dodge ||
		IncomingKey == EBufferKey::EBK_ConsumeItem ||
		IncomingKey == EBufferKey::EBK_Parry ||
		IncomingKey == EBufferKey::EBK_Interact
		)
	{
		return true;
	}
	return false;
}

void UVorpisUncursedInputBufferComponent::ResetBuffer()
{
	CurrentKey = EBufferKey::EBK_None;
	IsBufferOpen = true;
	CanChangeKey = true;
	bResetBuffer = true;
}