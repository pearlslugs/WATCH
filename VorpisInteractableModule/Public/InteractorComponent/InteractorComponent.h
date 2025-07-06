// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "AlsCameraComponent.h"
#include "InteractorComponent.generated.h"

class UCameraComponent;
class IInteractableInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShowIntneractPrompt, bool, Show);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VORPISINTERACTABLEMODULE_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractorComponent();
	UPROPERTY(BlueprintAssignable)
	FShowIntneractPrompt ShowIntneractPrompt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactor")
	float InteractionDistance = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactor")
	AActor* OwnerActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactor")
	bool CheckForInteractable = true;
	UFUNCTION()
	void SetCheckForInteractable(bool Condition) { CheckForInteractable = Condition; }
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactor")
	AActor* CurrentInteractable;
	UFUNCTION(BlueprintPure)
	AActor* GetCurrentInteractable() { return CurrentInteractable; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactor")
	AActor* PreviousInteractable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactor")
	bool CanInteract = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactor")
	USphereComponent* SphereComponent;

	UFUNCTION(BlueprintCallable, Category = "Interactor")
	void CheckForInteractables();
	UFUNCTION(BlueprintCallable, Category = "Interactor")
	void CheckForInteractablesFirstPerson();
	UFUNCTION(BlueprintCallable, Category = "Interactor")
	void Interact();
	UFUNCTION(BlueprintCallable, Category = "Interactor")
	void GetOwnerActor();
	UFUNCTION(BlueprintCallable, Category = "Interactor")
	void StartCheckingForInteractables();
	UFUNCTION(BlueprintCallable, Category = "Interactor")
	void SetCanInteract(bool NewCanInteract);
	UFUNCTION(BlueprintCallable, Category = "Interactor")
	void StopCheckingForInteractables();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool FirstPerson = true;
	UFUNCTION(BlueprintCallable)
	void SetFirstPerson(bool NewFirstPerson) { FirstPerson = NewFirstPerson; }
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAlsCameraComponent* AlsCamera;
	UFUNCTION(BlueprintCallable)
	void SetCameraOwner(UAlsCameraComponent* NewCamera) { AlsCamera = NewCamera; }
	UFUNCTION()
	void AssessInteractable(AActor* ActorReference);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
