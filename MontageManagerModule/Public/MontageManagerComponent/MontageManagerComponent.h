// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MontageData/MontageStructs.h"
#include "MontageManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboFinished);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONTAGEMANAGERMODULE_API UMontageManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMontageManagerComponent();

	UPROPERTY(BlueprintAssignable, Category = "Montage Manager")
	FOnComboFinished OnComboFinished;

	UFUNCTION(BlueprintCallable, Category = "Montage Manager")
	UAnimMontage* GetAttackMontage(ECombatPosition CombatPosition, bool UseAlternative = false, int Combo = 0);
	UFUNCTION(BlueprintCallable, Category = "Montage Manager")
	UAnimMontage* GetHitReactionMontage(ECombatPosition CombatPosition);
	UFUNCTION(BlueprintCallable, Category = "Montage Manager")
	UAnimMontage* GetBlockReactionMontage(ECombatPosition CombatPosition, bool UseAlternative);
	UFUNCTION(BlueprintCallable, Category = "Montage Manager")
	void SetCurrentCombatMontages(FDirectionalMontages Montages) { CurrentCombatMontages = Montages; }
	UFUNCTION(BlueprintCallable, Category = "Montage Manager")
	void SetHitReactionMontages(FDirectionalMontages Montages) { HitReactionMontages = Montages; }
	UFUNCTION(BlueprintCallable, Category = "Montage Manager")
	void SetBlockReactionMontages(FDirectionalMontages Montages) { BlockReactionMontages = Montages; }

	UFUNCTION(BlueprintCallable, Category = "Ownere Mesh")
	void SetOwnerMesh(USkeletalMeshComponent* Mesh) { OwnerMesh = Mesh; }
	UFUNCTION(BlueprintCallable, Category = "Owner Mesh")
	void PlaySelectedMontage(UAnimMontage* Montage);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Montages")
	FDirectionalMontages CurrentCombatMontages;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Montages")
	FDirectionalMontages HitReactionMontages;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Montages")
	FDirectionalMontages BlockReactionMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Owner Mesh")
	USkeletalMeshComponent* OwnerMesh;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


		
};
