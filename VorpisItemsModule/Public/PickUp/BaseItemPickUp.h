// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "ItemData/ItemStructs.h"
#include "Components/WidgetComponent.h"
#include "Interface/InteractableInterface.h"
#include "BaseItemPickUp.generated.h"

UCLASS()
class VORPISITEMSMODULE_API ABaseItemPickUp : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItemPickUp();

	// mesh data
	UPROPERTY()
	UStaticMeshComponent* MeshComponent = nullptr;


	// widget data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", Meta=(ExposeOnSpawn = true))
	TSubclassOf<UUserWidget> InteractWidget = nullptr;
	UPROPERTY()
	UWidgetComponent* InteractWidgetComponent = nullptr;

	// item data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", Meta=(ExposeOnSpawn = true))
	FItemData ItemData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// interface functions
	virtual void Interact_Implementation(AActor* Interactor) override;
	virtual void SecondaryInteract_Implementation(AActor* Interactor) override;
};
