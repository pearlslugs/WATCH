// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCombatComponent/BaseCombatComponent.h"

// Sets default values for this component's properties
UBaseCmbatComponent::UBaseCmbatComponent()
{
	CombatPosition = ECombatPosition::ECP_None;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseCmbatComponent::BeginPlay()
{
	Super::BeginPlay();

	CallUnlockPosition.BindUFunction(this, FName("ResetPositionLock"));
	CallResetCombo.BindUFunction(this, FName("ResetCombo"));
	// ...
	
}

void UBaseCmbatComponent::ResetPositionLock()
{
	PositionLock = false;
}


// Called every frame
void UBaseCmbatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseCmbatComponent::SetCombatPosition(ECombatPosition NewCombatPosition)
{
	if (GetCombatPosition() == ECombatPosition::ECP_None) 
	{
		CombatPosition = ECombatPosition::ECP_Right;
		OnCombatPositionChange.Broadcast(CombatPosition);
	}
	if (NewCombatPosition == ECombatPosition::ECP_None) return;
	if (NewCombatPosition == GetCombatPosition()) return;
	PositionLock = true;
	GetWorld()->GetTimerManager().SetTimer(ResetPositionLockTimer, CallUnlockPosition, PositionLockTime, false);
	CombatPosition = NewCombatPosition;
	OnCombatPositionChange.Broadcast(CombatPosition);
}

ECombatPosition UBaseCmbatComponent::GetCombatPositionFromVector2D(FVector2D Direction)
{
	if (PositionLock) return ECombatPosition::ECP_None;
	if (Direction.X < 0.2f && Direction.Y < 0.2) return ECombatPosition::ECP_None;
	if (Direction.X > 0.5 && FMath::Abs(Direction.X) > FMath::Abs(Direction.Y)) return ECombatPosition::ECP_Right;
	if (Direction.X < -0.5 && FMath::Abs(Direction.X) > FMath::Abs(Direction.Y)) return ECombatPosition::ECP_Left;
	if (Direction.Y > 0.5) return ECombatPosition::ECP_High;
	return ECombatPosition::ECP_None;
}

void UBaseCmbatComponent::ResetCombo()
{
	ComboCount = 0;
}

void UBaseCmbatComponent::StartComboTimer()
{
	GetWorld()->GetTimerManager().SetTimer(ComboTimer, CallResetCombo, ComboResetTime, false);
}
void UBaseCmbatComponent::ResetComboTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(ComboTimer);
	StartComboTimer();
}

void UBaseCmbatComponent::IncrimentComboCount()
{
	ComboCount++;
	StartComboTimer();
}