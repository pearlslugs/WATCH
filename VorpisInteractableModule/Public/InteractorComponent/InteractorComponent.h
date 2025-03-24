// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "InteractorComponent.generated.h"

class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VORPISINTERACTABLEMODULE_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractorComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactor")
	float InteractionDistance = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactor")
	AActor* OwnerActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactor")
	bool CheckForInteractable = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactor")
	AActor* CurrentInteractable;
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
	bool FirstPerson;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UCameraComponent* OwnerCamera;
	UFUNCTION(BlueprintCallable)
	void SetCameraOwner(UCameraComponent* NewCamera) { OwnerCamera = NewCamera; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
