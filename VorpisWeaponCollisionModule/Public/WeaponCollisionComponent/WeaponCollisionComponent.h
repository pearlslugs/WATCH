// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatData/CombatStructs.h"
#include "Math/TransformNonVectorized.h"
#include "WeaponCollisionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponHitActor, AActor*, HitActor, FHitTraceResults, HitResults);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VORPISWEAPONCOLLISIONMODULE_API UWeaponCollisionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UWeaponCollisionComponent();

	UPROPERTY(BlueprintAssignable)
	FOnWeaponHitActor OnWeaponHitActor;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* ItemStaticMesh;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
	bool IsStaticMesh = true;
	UFUNCTION(BlueprintPure)
	FORCEINLINE UStaticMeshComponent* GetItemStaticMesh() { return ItemStaticMesh; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetItemStaticMesh(UStaticMeshComponent* InStaticMesh) { ItemStaticMesh = InStaticMesh; }
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
	USkeletalMeshComponent* ItemSkeletalMesh;

	UPROPERTY()
	TArray<AActor*> IgnoredActors;
	TArray< UPrimitiveComponent*> IgnoredComponents;
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetActorOwner(AActor* InActor) { OwnerActor = InActor; }

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* OwnerActor;
	UPROPERTY()
	bool IsTraceOpen = false;
	UPROPERTY()
	FName ImpactSocketName;

	UPROPERTY()
	FHitTraceResults HitTraceResults;
	UFUNCTION(BlueprintCallable)
	void InitializeStaticMesh(UStaticMeshComponent* InStaticMesh);

	UFUNCTION(BlueprintCallable)
	void InitializeCollisionComponent(bool InIsStaticMesh, UStaticMeshComponent* InItemMesh, USkeletalMeshComponent* InSKMesh);
	UFUNCTION(BlueprintCallable)
	void TraceForHits();
	UFUNCTION(BlueprintCallable)
	void ToggleGate(bool Open);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Team stuff
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//EHostilityTeam OwnerTeam;
	//UFUNCTION(BlueprintPure)
	//EHostilityTeam GetOwnerTeam() { return OwnerTeam; }
	//UFUNCTION(BlueprintCallable)
	//void SetOwnerTeam(EHostilityTeam InTeam) { OwnerTeam = InTeam; }
		
};
