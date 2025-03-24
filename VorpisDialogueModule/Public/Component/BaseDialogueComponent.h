// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueData/DialogueDataAsset.h"
#include "BaseDialogueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VORPISDIALOGUEMODULE_API UBaseDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseDialogueComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	UDialogueDataAsset* DialogueDataAsset;
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetDialogueAsset(UDialogueDataAsset* NewDialogueDataAsset) { DialogueDataAsset = NewDialogueDataAsset; };
	UFUNCTION(BlueprintPure)
	UDialogueDataAsset* GetDialogueDataAsset() { return DialogueDataAsset; };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	AActor* DialogueTarget;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
