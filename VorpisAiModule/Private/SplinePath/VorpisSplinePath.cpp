// Fill out your copyright notice in the Description page of Project Settings.


#include "SplinePath/VorpisSplinePath.h"
#include "Components/SplineComponent.h"
// Sets default values
AVorpisSplinePath::AVorpisSplinePath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVorpisSplinePath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVorpisSplinePath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AVorpisSplinePath::GetVectorFromCurrentPoint()
{
	USplineComponent* CurrentSplineComponent = SplineComponents[SplinePath.CurrentPathGuid];
	if (CurrentSplineComponent != nullptr) {
			return CurrentSplineComponent->GetLocationAtSplinePoint(SplinePath.CurrentPointOnPath, ESplineCoordinateSpace::World);
	}
	return FVector::ZeroVector;
}

USplineComponent* AVorpisSplinePath::GetCurrentSplineComponent()
{
	if (SplineComponents.Contains(SplinePath.CurrentPathGuid)) {
		return SplineComponents[SplinePath.CurrentPathGuid];
	}
	return nullptr;
}