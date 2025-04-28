// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatData/CombatEnums.h"
#include "BaseCombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatPositionChange, ECombatPosition, CombatPosition);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBATCOMPONENTMODULE_API UBaseCmbatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseCmbatComponent();
	FTimerHandle ResetPositionLockTimer;
	float PositionLockTime = 0.2f;
	FTimerDynamicDelegate CallUnlockPosition;
	UFUNCTION()
	void ResetPositionLock();
	UPROPERTY()
	bool PositionLock = false;

	//combo 
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	int ComboCount = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	int HitCount = 0;
	UFUNCTION()
	void ResetHitCount() { HitCount = 0; };
	UFUNCTION()
	void IncreaseHitCount();
	FTimerHandle HitTimer;
	float ResetHitCountTimerTime = 3.f;
	FTimerDynamicDelegate CallResetHitCount;

	UFUNCTION()
	int GetComboCount() { return ComboCount; };
	FTimerHandle ComboTimer;
	float ComboResetTime = 2.2f;
	FTimerDynamicDelegate CallResetCombo;
	UFUNCTION(BlueprintCallable)
	void ResetCombo();
	UFUNCTION()
	void StartComboTimer();
	UFUNCTION()
	void ResetComboTimer();
	UFUNCTION() void IncrimentComboCount();
	

	UPROPERTY(BlueprintAssignable)
	FOnCombatPositionChange OnCombatPositionChange;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetCombatPosition(ECombatPosition NewCombatPosition);
	UFUNCTION(BlueprintPure, Category = "Combat")
	ECombatPosition GetCombatPosition() const { return CombatPosition; }

	UFUNCTION()
	ECombatPosition GetCombatPositionFromVector2D(FVector2D Direction);



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	ECombatPosition CombatPosition;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
