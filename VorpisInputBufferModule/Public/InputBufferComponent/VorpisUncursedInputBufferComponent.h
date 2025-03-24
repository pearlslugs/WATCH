// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputBufferData/InputBufferEnums.h"
#include "VorpisUncursedInputBufferComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBufferConsumed, EBufferKey, KeyToConsume);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBufferSwitch, bool, BufferState);



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VORPISINPUTBUFFERMODULE_API UVorpisUncursedInputBufferComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UVorpisUncursedInputBufferComponent();

	UPROPERTY(BlueprintAssignable)
	FOnBufferConsumed OnBufferConsumed;
	UPROPERTY(BlueprintAssignable)
	FOnBufferSwitch OnBufferSwitch;
	UFUNCTION(BlueprintCallable)
	void OpenBuffer();
	UFUNCTION(BlueprintCallable)
	void ConsumeBuffer();
	UFUNCTION(BlueprintCallable)
	void PreventEarlyInput();

	UFUNCTION(BlueprintCallable)
	void AcceptKey(EBufferKey InKey);
	UFUNCTION(BlueprintCallable)
	void ResetBuffer();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bResetBuffer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly)
	EBufferKey CurrentKey;
	UPROPERTY(BlueprintReadOnly)
	bool IsBufferOpen;
	UPROPERTY(BlueprintReadOnly)
	bool ShouldConsumeCurrentKey;
	UPROPERTY(BlueprintReadOnly)
	bool CanChangeKey; // may be redundant
	UPROPERTY(BlueprintReadOnly)
	bool IsInputQued;

	EAuxBufferKey CurrentAuxBufferKey;
	bool CanUseAuxInput;

	UFUNCTION()
	bool CompareKeys(EBufferKey IncomingKey);
	bool GetIsHighPriorityInput(EBufferKey IncomingKey);


	UFUNCTION()
	void CloseBuffer();

	UFUNCTION()
	void ClearBuffer();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
