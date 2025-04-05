// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BaseAttackAndDefenseWidget.h"

void UBaseAttackAndDefenseWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseAttackAndDefenseWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	if (GetIsTargetDifferent())
	{
		CurrentDefenseAngleFloat = FMath::Lerp(CurrentDefenseAngleFloat, TargetDefenseAngleFloat, DeltaTime * 5);
		CurrentOffenceAngleFloat = FMath::Lerp(CurrentOffenceAngleFloat, TargetOffenceAngleFloat, DeltaTime * 5);
		if (FMath::IsNearlyEqual(CurrentDefenseAngleFloat, TargetDefenseAngleFloat, 1) && FMath::IsNearlyEqual(CurrentOffenceAngleFloat, TargetOffenceAngleFloat, 1))
		{
			CurrentDefenseAngleFloat = TargetDefenseAngleFloat;
			CurrentOffenceAngleFloat = TargetOffenceAngleFloat;
			SetIsTargetDifferent(false);
		}
	}
}

void UBaseAttackAndDefenseWidget::SetDefensePosition(ECombatPosition NewDefensePosition)
{
	if (NewDefensePosition == CurrentDefensePosition) return;
	switch (NewDefensePosition)
	{
	case ECombatPosition::ECP_Left:
		SetTargetDefenseAngleFloat(LeftTargetAngleFloat);
		break;
	case ECombatPosition::ECP_Right:
		SetTargetDefenseAngleFloat(RightTargetAngleFloat);
		break;
	case ECombatPosition::ECP_High:
		SetTargetDefenseAngleFloat(HighTargetAngleFloat);
		break;
	default:
		break;
	}
	CurrentDefensePosition = NewDefensePosition;
	SetIsTargetDifferent(true);
}
void UBaseAttackAndDefenseWidget::SetOffencePosition(ECombatPosition NewOffencePosition)
{
	if (!GEngine) return;
	FString Postion = *UEnum::GetValueAsName(NewOffencePosition).ToString();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, Postion);
	switch (NewOffencePosition)
	{
	case ECombatPosition::ECP_Left:
		SetTargetOffenceAngleFloat(OuterLeftTargetAngleFloat);
		break;
	case ECombatPosition::ECP_Right:
		SetTargetOffenceAngleFloat(OuterRightTargetAngleFloat);
		break;
	case ECombatPosition::ECP_High:
		SetTargetOffenceAngleFloat(OuterHighTargetAngleFloat);
		break;
	default:
		break;
	}
	CurrentOffencePosition = NewOffencePosition;
	SetIsTargetDifferent(true);
}