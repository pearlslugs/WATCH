// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoliageData/FoliageData.h"
#include "BaseFoliageSpawner.generated.h"

UCLASS()
class VORPISFOLIAGEMODULE_API ABaseFoliageSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseFoliageSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foliage Data")
	TMap<EFoliageType, int> FoliageMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foliage Data")
	TMap<EFoliageType, UStaticMesh*> FoliageMeshMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foliage Data")
	float MaxXRotation = 15;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foliage Data")
	float MinXRotatation = -15;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foliage Data")
	float MaxYRotation = 15;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foliage Data")
	float MinYRotata = -15;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foliage Data")
	float MaxZRotation = 360;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foliage Data")
	float MinZRotatation = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foliage Data")
	float MaxScale = 1.3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foliage Data")
	float MinScale = 0.7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foliage Data")
	float Range = 1200;

	UFUNCTION(BlueprintCallable)
	FTransform MakeRandomTransform(FVector Location);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
