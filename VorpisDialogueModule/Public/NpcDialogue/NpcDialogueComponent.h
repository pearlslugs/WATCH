// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component/BaseDialogueComponent.h"
#include "NpcDialogueComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginDialogue, UDialogueDataAsset*, Dialogue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndDialogue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VORPISDIALOGUEMODULE_API UNpcDialogueComponent : public UBaseDialogueComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNpcDialogueComponent();

	UPROPERTY(BlueprintAssignable)
	FOnBeginDialogue OnBeginDialogue;
	UPROPERTY(BlueprintAssignable)
	FOnEndDialogue OnEndDialogue;

	UFUNCTION(BlueprintCallable)
	void BeginDialogue();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
