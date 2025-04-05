// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatData/CombatEnums.h"
#include "BaseAttackAndDefenseWidget.generated.h"

/**
 * 
 */
UCLASS()
class VORPISATTACKANDDEFENCEWHEEL_API UBaseAttackAndDefenseWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Defense")
	void SetDefensePosition(ECombatPosition NewDefensePosition);
	UFUNCTION(BlueprintCallable, Category = "Offence")
	void SetOffencePosition(ECombatPosition NewOffencePosition);

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	ECombatPosition CurrentDefensePosition;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	ECombatPosition CurrentOffencePosition;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float TargetDefenseAngleFloat = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float CurrentDefenseAngleFloat = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float TargetOffenceAngleFloat = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float CurrentOffenceAngleFloat = 0;

	UFUNCTION()
	void SetTargetDefenseAngleFloat(float Target) { TargetDefenseAngleFloat = Target; }
	UFUNCTION()
	void SetTargetOffenceAngleFloat(float Target) { TargetOffenceAngleFloat = Target; }

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float RightTargetAngleFloat = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float LeftTargetAngleFloat = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float HighTargetAngleFloat = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float OuterRightTargetAngleFloat = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float OuterLeftTargetAngleFloat = 0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float OuterHighTargetAngleFloat = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool IsTargetDifferent = false;
	UFUNCTION()
	void SetIsTargetDifferent(bool NewCondition) { IsTargetDifferent = NewCondition; };
	UFUNCTION()
	bool GetIsTargetDifferent() { return IsTargetDifferent; };
	
};
