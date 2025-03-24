// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "VorpisPlayerController.generated.h"


/**
 *
 */
UCLASS()
class VORPISCONTROLLERS_API AVorpisPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AVorpisPlayerController();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputMappingContext> ControllerMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> ControllerUpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> ControllerDownAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> ControllerLeftAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> ControllerRightAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> ControllerSelectAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Input")
	TObjectPtr<UInputAction> ControllerBackAction;

	UFUNCTION()
	void SetControlledActor(AActor* NewActor) { ControlledActor = NewActor; };
	UFUNCTION()
	void SetMountedWidget(UUserWidget* Widget) { MountedWidget = Widget; };
	UFUNCTION()
	void SetMountedComponent(UActorComponent* Component) { MountedComponent = Component; };

	UFUNCTION()
	AActor* GetControlledActor() { return ControlledActor; };
	UFUNCTION()
	UUserWidget* GetMountedWidget() { return MountedWidget; };
	UFUNCTION()
	UActorComponent* GetMountedComponent() { return MountedComponent; };


protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vorpis")
	UActorComponent* WidgetControllerComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vorpis")
	AActor* ControlledActor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vorpis")
	UUserWidget* MountedWidget = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vorpis")
	UActorComponent* MountedComponent = nullptr;

	// Input Actions
	void Input_ControllerUp();
	void Input_ControllerDown();
	void Input_ControllerLeft();
	void Input_ControllerRight();
	void Input_ControllerSelect();
	void Input_ControllerBack();
	void Input_ControllerStart();
};
