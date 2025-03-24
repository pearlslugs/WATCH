// Fill out your copyright notice in the Description page of Project Settings.


#include "FoliageBlocker.h"
#include "Components/BoxComponent.h"

// Sets default values
AFoliageBlocker::AFoliageBlocker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionObjectType(ECC_WorldDynamic);
	Tags.Add(FoliageBlockerTag);
}

// Called when the game starts or when spawned
void AFoliageBlocker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFoliageBlocker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

