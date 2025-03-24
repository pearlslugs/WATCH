// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseFoliageSpawner.h"
#include "NavigationSystem.h"
#include "FoliageNavFilter.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
ABaseFoliageSpawner::ABaseFoliageSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FTransform ABaseFoliageSpawner::MakeRandomTransform(FVector Location)
{
	FRotator tet = FRotator(0, 0, 0);
	float RandomScale = FMath::RandRange(MinScale, MaxScale);
		return FTransform(
		{ FMath::RandRange(MinXRotatation, MaxXRotation), FMath::RandRange(MinZRotatation, MaxZRotation), FMath::RandRange(MinXRotatation, MaxYRotation)},
		Location,
		{ RandomScale, RandomScale, RandomScale }
	);
}

// Called when the game starts or when spawned
void ABaseFoliageSpawner::BeginPlay()
{
	Super::BeginPlay();
	for (auto& Map : FoliageMap)
	{
		UInstancedStaticMeshComponent* NewMesh = Cast<UInstancedStaticMeshComponent>(AddComponentByClass(UInstancedStaticMeshComponent::StaticClass(), false, FTransform(), false));
		if (FoliageMeshMap.Contains(Map.Key)) {
			NewMesh->SetStaticMesh(FoliageMeshMap[Map.Key]);
			for (int i = 0; i < Map.Value; i++) {
				FVector Location;
				if (UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(GetWorld(), GetActorLocation(), Location, Range)) {
					FTransform NewTransform = ABaseFoliageSpawner::MakeRandomTransform(Location);
					FHitResult HitResult;
					GetWorld()->LineTraceSingleByObjectType(HitResult, Location + FVector(0, 0, 400), Location + FVector(0, 0, -1000), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic), FCollisionQueryParams());
					if (HitResult.GetActor() != nullptr) {
						if (HitResult.GetActor()->Tags.Contains("FoliageBlocker")) {
							continue;
						}
					}
					NewMesh->AddInstance(NewTransform, true);
				}
			}
		}
	}
	
}

// Called every frame
void ABaseFoliageSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

