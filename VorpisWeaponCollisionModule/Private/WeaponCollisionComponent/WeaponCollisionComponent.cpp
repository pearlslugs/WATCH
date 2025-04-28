// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponCollisionComponent/WeaponCollisionComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BaseInterface/BaseRpgCharacterInterface.h"
#include "Components/SkinnedMeshComponent.h"

// Sets default values for this component's properties
UWeaponCollisionComponent::UWeaponCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UWeaponCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsTraceOpen && IsValid(ItemStaticMesh))
	{
		TraceForHits();
	}

	// ...
}



void UWeaponCollisionComponent::InitializeCollisionComponent(bool InIsStaticMesh, UStaticMeshComponent* InItemMesh, USkeletalMeshComponent* InSKMesh)
{
	IsStaticMesh = InIsStaticMesh;
	if (InIsStaticMesh)
	{
		ItemStaticMesh = InItemMesh;

	}
	else
	{
		// get bone locations
	}
}
void UWeaponCollisionComponent::TraceForHits()
{
	if (IsStaticMesh)
	{
		TArray<FHitResult> OutHits;
		TArray<AActor*> ActorsToIgnore = IgnoredActors;
		ActorsToIgnore.Add(GetOwner());
		FVector StartLocation = ItemStaticMesh->GetSocketLocation("StartSocket");
		FVector EndLocation = ItemStaticMesh->GetSocketLocation("EndSocket");

		float CapsuleRadius = 15.0f;
		float CapsuleHalfHeight = 15.0f;

		bool bHit = UKismetSystemLibrary::CapsuleTraceMulti(
			this,
			StartLocation,
			EndLocation,
			CapsuleRadius,
			CapsuleHalfHeight,
			UEngineTypes::ConvertToTraceType(ECC_Pawn),
			false, 
			ActorsToIgnore,
			EDrawDebugTrace::None,
			OutHits,
			true
		);

		if (bHit)
		{
			for (const FHitResult& Hit : OutHits)
			{
				AActor* HitActor = Hit.GetActor();
				if (HitActor && !IgnoredActors.Contains(HitActor))
				{
					IgnoredActors.Add(HitActor);
					IBaseRpgCharacterInterface* InterfaceActor = Cast<IBaseRpgCharacterInterface>(HitActor);

					if (InterfaceActor)
					{
						FHitTraceResults CurrentHitTraceResults;
						CurrentHitTraceResults.HitLocation = Hit.ImpactPoint;
						CurrentHitTraceResults.AttackerLocation = GetOwner()->GetActorLocation();
						CurrentHitTraceResults.HitBone = InterfaceActor->GetSkinnedMesh()->FindClosestBone(Hit.ImpactPoint);
						OnWeaponHitActor.Broadcast(HitActor, CurrentHitTraceResults);
					}
				}
			}
		}
	}
}


void UWeaponCollisionComponent::ToggleGate(bool Open)
{
	if (!IsValid(ItemStaticMesh)) {
		return;
	}
	PrimaryComponentTick.bCanEverTick = Open;
	IsTraceOpen = Open;
	if (!Open)
	{

		IgnoredActors.Empty();
		return;
	}
	else {
		ItemStaticMesh->SetGenerateOverlapEvents(true);
	}
}

void UWeaponCollisionComponent::InitializeStaticMesh(UStaticMeshComponent* InMesh)
{
	if (InMesh)
	{
		ItemStaticMesh = InMesh;
	}
}