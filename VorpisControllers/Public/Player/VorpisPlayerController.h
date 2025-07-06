// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerControllerInterface/VorpisPlayerControllerInterface.h"
#include "ControllerData/ControllerEnums.h"
#include "VorpisPlayerController.generated.h"

/**
 *
 */
UCLASS()
class VORPISCONTROLLERS_API AVorpisPlayerController : public APlayerController, public IVorpisPlayerControllerInterface
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

	UFUNCTION(BlueprintCallable)
	void SetControlledActor(AActor* NewActor) { ControlledActor = NewActor; };
	UFUNCTION(BlueprintCallable)
	void SetMountedWidget(UUserWidget* Widget) { MountedWidget = Widget; };
	UFUNCTION(BlueprintCallable)
	void SetMountedComponent(UActorComponent* Component) { MountedComponent = Component; };

	UFUNCTION(BlueprintPure)
	AActor* GetControlledActor() { return ControlledActor; };
	UFUNCTION(BlueprintPure)
	UUserWidget* GetMountedWidget() { return MountedWidget; };
	UFUNCTION(BlueprintPure)
	UActorComponent* GetMountedComponent() { return MountedComponent; };

	UFUNCTION(BlueprintPure)
	EControllerMenuType GetCurrentMenu() { return CurrentMenu; }
	UFUNCTION(BlueprintCallable)
	void SetControllerMenuType(EControllerMenuType NewMenu);

	// UI
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddErrorMessage(const FString& Message);
	void AddErrorMessage_Implementation(const FString& Message) {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ShowInteractPrompt(bool Condition);
	void ShowInteractPrompt_Implementation(bool Condition) {};
	UFUNCTION(BlueprintCallable)
	void SetQuickslotsWidget(UUserWidget* NewWidget) { QuickslotsWidget = NewWidget; }
	UFUNCTION(BlueprintPure)
	UUserWidget* GetQuickslotsWidget() { return QuickslotsWidget; }
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateQuickslots(int Quickslot, bool Hovered, bool Selected);
	void  UpdateQuickslots_Implementation(int Quickslot, bool Hovered, bool Selected) {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SwapToNormalUI();
	void SwapToNormalUI_Implementation() {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SwapToHarvestUI();
	void SwapToHarvestUI_Implementation() {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateMashProgressBar(float Progress);
	void UpdateMashProgressBar_Implementation(float Progress) {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleMashUI(bool Condition);
	void ToggleMashUI_Implementation(bool Condition) {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleProgressBarUI(bool Condition);
	void ToggleProgressBarUI_Implementation(bool Condition) {};
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float IncrimentProgressBar(float Amount);
	float IncrimentProgressBar_Implementation(float Amount) { return -1.f; };
	float InterfaceIncrimentProgressBar_Implementation(float Amount) { return -1.f; };

	UFUNCTION(BlueprintCallable)
	void SetProgressWidget(UUserWidget* NewWidget) { ProgressWidget = NewWidget; }
	UFUNCTION(BlueprintPure)
	UUserWidget* GetProgressWidget() { return ProgressWidget; }
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UActorComponent* WidgetControllerComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* ControlledActor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UUserWidget* MountedWidget = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UActorComponent* MountedComponent = nullptr;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EControllerMenuType CurrentMenu;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UUserWidget* QuickslotsWidget;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UUserWidget* ProgressWidget;

public:
	// Input Actions
	UFUNCTION(BlueprintCallable)
	void Input_ControllerUp();
	void Input_ControllerDown();
	UFUNCTION(BlueprintCallable)
	void Input_ControllerLeft();
	UFUNCTION(BlueprintCallable)
	void Input_ControllerRight();
	UFUNCTION(BlueprintCallable)
	void Input_ControllerSelect();
	UFUNCTION(BlueprintCallable)
	void Input_ControllerBack();
	UFUNCTION(BlueprintCallable)
	void Input_ControllerStart();
};
