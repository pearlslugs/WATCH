// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractorComponent/InteractorComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/InteractableInterface.h"

// Sets default values for this component's properties
UInteractorComponent::UInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(false);
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(InteractionDistance);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAll"));

	// ...
}


// Called when the game starts
void UInteractorComponent::BeginPlay()
{
	Super::BeginPlay();
	UInteractorComponent::GetOwnerActor();
	if (OwnerActor) {
		SphereComponent->SetupAttachment(OwnerActor->GetRootComponent());
	}
	// ...
	
}


// Called every frame
void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CheckForInteractable) {
		if (FirstPerson) {
			CheckForInteractablesFirstPerson();
		}
		else {
			CheckForInteractables();
		}
	} else {
		SetComponentTickEnabled(false);
	}

	// ...
}

void UInteractorComponent::CheckForInteractables()
{
	if (CheckForInteractable && IsValid(OwnerActor)) {
		float CurrentDistanceFromOwner = 99999.f;
		TArray<AActor*> OverlappingActors;
		SphereComponent->GetOverlappingActors(OverlappingActors);
		for (AActor* Actor : OverlappingActors) {
			if (Actor == OwnerActor) continue;
			if (Actor->Implements<UInteractableInterface>()) {
				float Distance = FVector::Dist(OwnerActor->GetActorLocation(), Actor->GetActorLocation());
				if (Distance < CurrentDistanceFromOwner) {
					CurrentInteractable = Actor;
					CurrentDistanceFromOwner = Distance;
					ShowIntneractPrompt.Broadcast(true);
				}
			}
		}
	} 
	else {
		CurrentInteractable = nullptr;
		PreviousInteractable = nullptr;
		ShowIntneractPrompt.Broadcast(true);
		SetComponentTickEnabled(false);
	}
}

void UInteractorComponent::CheckForInteractablesFirstPerson()
{
	if (CheckForInteractable && IsValid(AlsCamera)) {
		TArray<FHitResult> OutHits;
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(GetOwner());
		FVector StartLocation = AlsCamera->GetFirstPersonCameraLocation();
		FVector Rotation = AlsCamera->GetCameraRotation().Vector();
		FVector EndLocation = StartLocation + (Rotation * 200);

		bool bHit = UKismetSystemLibrary::LineTraceMulti(
			this,
			StartLocation,
			EndLocation,
			UEngineTypes::ConvertToTraceType(ECC_Camera),
			false,
			ActorsToIgnore,
			EDrawDebugTrace::ForOneFrame,
			OutHits,
			true
		);
		bool FoundInteractable = false;;
		if (bHit) {
			for (FHitResult &Hit : OutHits) {
				if (Hit.GetActor()->Implements<UInteractableInterface>()) {
					AssessInteractable(Hit.GetActor());
					FoundInteractable = true;
					break;
				}
			}
			if (!FoundInteractable) {
				if (CurrentInteractable) {
					IInteractableInterface* NewInteractable = Cast<IInteractableInterface>(CurrentInteractable);
					if (NewInteractable) {
						ShowIntneractPrompt.Broadcast(false);
						NewInteractable->ToggleHovered(false);
						CurrentInteractable = nullptr;
					}
				}
			}
		}
		else {
			if (CurrentInteractable) {
				IInteractableInterface* NewInteractable = Cast<IInteractableInterface>(CurrentInteractable);
				if (NewInteractable) {
					NewInteractable->ToggleHovered(false);
				}
			}
			ShowIntneractPrompt.Broadcast(false);
			CurrentInteractable = nullptr;
		}
	}
}

void UInteractorComponent::AssessInteractable(AActor* ActorReference)
{
	if (CurrentInteractable == ActorReference) return;
	PreviousInteractable = CurrentInteractable;
	CurrentInteractable = ActorReference;
	IInteractableInterface* PreviousInteractableInterface = Cast<IInteractableInterface>(PreviousInteractable);
	IInteractableInterface* NewInteractable = Cast<IInteractableInterface>(CurrentInteractable);
	if (PreviousInteractableInterface) {
		PreviousInteractableInterface->ToggleHovered(false);
	}
	if (NewInteractable) {
		ShowIntneractPrompt.Broadcast(true);
		NewInteractable->ToggleHovered(true);
	}
}

void UInteractorComponent::Interact()
{
	if (CurrentInteractable) {
		IInteractableInterface* Interactable = Cast<IInteractableInterface>(CurrentInteractable);
		if (Interactable) {
			Interactable->Execute_Interact(CurrentInteractable, OwnerActor);
		}
	}
}
void UInteractorComponent::GetOwnerActor()
{
	OwnerActor = GetOwner();
}
void UInteractorComponent::StartCheckingForInteractables()
{
	SetComponentTickEnabled(true);
	CheckForInteractable = true;
	CheckForInteractables();	
}
void UInteractorComponent::SetCanInteract(bool NewCanInteract)
{
	CanInteract = NewCanInteract;
}
void UInteractorComponent::StopCheckingForInteractables()
{
	CheckForInteractable = false;
	SetComponentTickEnabled(false);
}

