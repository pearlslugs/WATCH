// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "VorpisSplinePath.generated.h"

class USplineComponent;

USTRUCT(BlueprintType)
struct FSplineSubPath
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGuid SubPathGuid;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int LastSplinePoint;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<int, FGuid> BranchingPoints;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString SubPathName;
};

USTRUCT(BlueprintType)
struct FSplinePath
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FSplineSubPath> SubPaths;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGuid StartSubPathGuid;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGuid CurrentPathGuid;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int CurrentPointOnPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsFinished;

	FSplineSubPath GetSubPath(FGuid SubPathGuid)
	{
		for (FSplineSubPath SubPath : SubPaths) {
			if (SubPath.SubPathGuid == SubPathGuid) {
				return SubPath;
			}
		}
		return FSplineSubPath();
	}

	void GoToNextPoint()
	{
		FSplineSubPath CurrentPath = GetSubPath(CurrentPathGuid);
		int NextPoint = CurrentPointOnPath + 1;
		if (CurrentPath.LastSplinePoint > NextPoint)
		{
			if (CurrentPath.BranchingPoints.Num() > 0)
			{
				if (CurrentPath.BranchingPoints.Contains(NextPoint))
				{
					// do we follow the main path or branch
					float Random = FMath::RandRange(0, 9);
					if (Random >= 5)
					{
						CurrentPathGuid = CurrentPath.BranchingPoints[NextPoint];
						CurrentPointOnPath = 0;
					}
					else
					{
						CurrentPointOnPath = NextPoint;
					}
				}
				else
				{
					CurrentPointOnPath = NextPoint;
				}
			}
			else
			{
				CurrentPointOnPath = NextPoint;
			}
		}
	};

};

class USplineComponent;

UCLASS()
class VORPISAIMODULE_API AVorpisSplinePath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVorpisSplinePath();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Path")
	FSplinePath SplinePath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Path")
	TMap<FGuid, USplineComponent*> SplineComponents;

	UFUNCTION()
	USplineComponent* GetCurrentSplineComponent();

	UFUNCTION()
	FVector GetVectorFromCurrentPoint();
	UFUNCTION()
	void GoToNextPoint() { SplinePath.GoToNextPoint(); };
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
