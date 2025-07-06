// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseInterface/BaseWidgetInterface.h"
#include "Component/BaseDialogueComponent.h"
#include "PlayerDialogueComponent.generated.h"

// this class acts as a controller for the dialogue widget
// it recieves an npc dialogue data asset and displays the dialogue options in the widget

// delagate to let the player know dialogue is over
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogueEndDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VORPISDIALOGUEMODULE_API UPlayerDialogueComponent : public UBaseDialogueComponent, public IBaseWidgetInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerDialogueComponent();

	UPROPERTY(BlueprintAssignable)
	FDialogueEndDelegate OnDialogueEnd;

	UFUNCTION(BlueprintCallable)
	void SetMountedWidget(UUserWidget* Widget);
	UFUNCTION(BlueprintPure)
	UUserWidget* GetMountedWidget() { return MountedWidget; };

	UFUNCTION(BlueprintCallable)
	void GoToNextDialogueOption(FGuid Guid);
	UFUNCTION(BlueprintCallable)
	void EndDialogue();

	UPROPERTY()
	int CurrentDialogueOptionIndex = 0;
	UPROPERTY()
	FGuid CurrentDialogueOptionId = FGuid();
	UFUNCTION(BlueprintPure)
	FGuid GetCurrentDialogueOptionId() { return CurrentDialogueOptionId; };

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	UUserWidget* MountedWidget = nullptr;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void WidgetUpInput_Implementation() override;
	virtual void WidgetDownInput_Implementation() override;
	virtual void WidgetLeftInput_Implementation() override;
	virtual void WidgetRightInput_Implementation() override;
	virtual void WidgetBackInput_Implementation() override;
	virtual void WidgetSelectInput_Implementation() override;
};
