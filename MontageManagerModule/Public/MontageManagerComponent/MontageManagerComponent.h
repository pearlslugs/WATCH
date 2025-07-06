// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MontageData/MontageStructs.h"
#include "ItemData/ItemEnums.h"
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
	UAnimMontage* GetHitReactionMontage(ECombatPosition CombatPosition, bool HitFromTheBack = false, int SpecificReaction = 0);
	UFUNCTION(BlueprintCallable, Category = "Montage Manager")
	UAnimMontage* GetBlockReactionMontage(ECombatPosition CombatPosition, bool UseAlternative);
	UFUNCTION(BlueprintCallable, Category = "Montage Manager")
	UAnimMontage* GetDodgeMontage(EDodgeDirection DodgeDirection);

	UFUNCTION(BlueprintCallable, Category = "Montage Manager")
	void SetCurrentCombatMontages(FDirectionalMontages Montages) { CurrentCombatMontages = Montages; }
	UFUNCTION(BlueprintCallable, Category = "Montage Manager")
	void SetHitReactionMontages(FDirectionalMontages Montages, UAnimMontage* NewHitFromTheBackMontage) { HitReactionMontages = Montages; HitFromTheBackMontage = NewHitFromTheBackMontage; }
	UFUNCTION(BlueprintCallable, Category = "Montage Manager")
	void SetBlockReactionMontages(FDirectionalMontages Montages) { BlockReactionMontages = Montages; }
	UFUNCTION(BlueprintCallable, Category = "Montage Manager")
	void SetDodgeMontages(TMap<EDodgeDirection, UAnimMontage*> NewDodges) { DodgeMontages = NewDodges; };

	UFUNCTION(BlueprintCallable, Category = "Ownere Mesh")
	void SetOwnerMesh(USkeletalMeshComponent* Mesh) { OwnerMesh = Mesh; }
	UFUNCTION(BlueprintCallable, Category = "Owner Mesh")
	void PlaySelectedMontage(UAnimMontage* Montage);
	UFUNCTION(BlueprintCallable)
	UAnimMontage* GetPickUpMontage(EEquipmentSlot ItemEquipSlot);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Montages")
	FDirectionalMontages CurrentCombatMontages;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Montages")
	FDirectionalMontages HitReactionMontages;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Montages")
	UAnimMontage* HitFromTheBackMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Montages")
	FDirectionalMontages BlockReactionMontages;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Montages")
	TMap<EDodgeDirection, UAnimMontage*> DodgeMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Owner Mesh")
	USkeletalMeshComponent* OwnerMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Owner Mesh")
	UAnimMontage* RightHandedPickUpMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Owner Mesh")
	UAnimMontage* LeftHandedPickUpMontage;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


		
};
