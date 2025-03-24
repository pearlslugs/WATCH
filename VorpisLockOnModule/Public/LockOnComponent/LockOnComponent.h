// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "Delegates/Delegate.h"
#include "Components/ActorComponent.h"
#include "LockOnComponent.generated.h"



// Forward Decarations
class UCameraComponent;
class APlayerCameraManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLockedOnChange, bool, CurrentlyLockedOn);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VORPISLOCKONMODULE_API ULockOnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULockOnComponent();

	UPROPERTY(BlueprintAssignable)
	FOnLockedOnChange OnLockedOn;

	FTimerHandle LockonTimerHandler;
	float LockOnInterval = 0.025f;
	FTimerDynamicDelegate ContinueLockingOn;
	UFUNCTION(BlueprintPure)
	bool GetIsLockedOn() { return IsLockedOn; }

	UFUNCTION(BlueprintCallable)
	void LockOn(bool LockOn);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* TargetedActor = nullptr;
	UPROPERTY()
	TArray<AActor*> PotentialTargets;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	APlayerCameraManager* PlayerCameraManager = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	APlayerController* PlayerController = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* CharacterOwner = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int TargetingTries = 0;
	UPROPERTY()
	bool IsTargeting = false;
	void SwitchTargetingCamera(bool ShouldBeEnabled);
	UFUNCTION()
	void ContinuousLockOn();
	UFUNCTION()
	void StopTargeting();
	UFUNCTION()
	bool FindClosestActor();
	UFUNCTION()
	void BeginTargeting();
	UFUNCTION(BlueprintCallable)
	void SwitchTarget(bool ToTheRight);
	UFUNCTION(BlueprintCallable)
	void OnEnemyKilled(AActor* KilledEnemy);
	UFUNCTION(BlueprintCallable)
	void FindNextTarget();

	void InitializeLockOnComponent(APlayerCameraManager* CameraManager, APlayerController* NewPlayerController, AActor* NewCharacterOwner);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsLockedOn = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
