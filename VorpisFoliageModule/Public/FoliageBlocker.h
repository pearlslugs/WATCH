// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoliageBlocker.generated.h"

UCLASS()
class VORPISFOLIAGEMODULE_API AFoliageBlocker : public AActor
{
	GENERATED_BODY()
	
public:	
	AFoliageBlocker();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Foliage Blocker")
	class UBoxComponent* BoxComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	FName FoliageBlockerTag = "FoliageBlocker";

};
