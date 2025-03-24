// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp/BaseItemPickUp.h"

// Sets default values
ABaseItemPickUp::ABaseItemPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	InteractWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidgetComponent"));
	InteractWidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseItemPickUp::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(ItemData.ItemAsset)) {
		MeshComponent->SetStaticMesh(ItemData.ItemAsset->BaseMeshes[0]);
		FVector LocationPlusZ = GetActorLocation() + FVector(0, 0, 200);
		SetActorLocation(LocationPlusZ);
		MeshComponent->SetSimulatePhysics(true);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("ItemAsset is not valid"));
		Destroy();
	}
	
}

// Called every frame
void ABaseItemPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseItemPickUp::Interact_Implementation(AActor* Interactor)
{
	// Default implementation of Interact
}

void ABaseItemPickUp::SecondaryInteract_Implementation(AActor* Interactor)
{
	// Default implementation of SecondaryInteract
}