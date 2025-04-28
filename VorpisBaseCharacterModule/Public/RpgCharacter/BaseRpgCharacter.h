// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentComponent/EquipmentComponent.h"
#include "CombatData/CombatEnums.h"
#include "BaseCombatComponent/BaseCombatComponent.h"
#include "WeaponCollisionComponent/WeaponCollisionComponent.h"
#include "CharacterStateComponent/CharacterStateComponent.h"
#include "MontageManagerComponent/MontageManagerComponent.h"
#include "GeneralData/GeneralData.h"
#include "DataAsset/ItemDataAsset.h"
#include "Components/CharacterStatusComponent.h"
#include "VorpisALSCharacter/VorpisBaseALSCharacter.h"
#include "BaseInterface/BaseRpgCharacterInterface.h"
#include "BaseRpgCharacter.generated.h"

/**
 * 
 */

class UNiagaraComponent;
class UNiagaraSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDisabled);


UCLASS()
class VORPISBASECHARACTERMODULE_API ABaseRpgCharacter : public AVorpisBaseALSCharacter, public IBaseRpgCharacterInterface
{
	GENERATED_BODY()
public:

	ABaseRpgCharacter();
	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;
	UPROPERTY(BlueprintAssignable)
	FOnCharacterDisabled OnCharacterDisabled;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FInitialAttackData CurrentInitialAttackData;
	// attack data
	UFUNCTION(BlueprintCallable)
	void SetAttackTraceData(FInitialAttackData TraceData) { CurrentInitialAttackData = TraceData; }
	UFUNCTION(BlueprintPure)
	FInitialAttackData GetAttackTraceData() { return CurrentInitialAttackData; };
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FFinishedAttackStruct CurrentAttack;

	// dodge
	UFUNCTION()
	void BaseDodge();
	UFUNCTION(BlueprintCallable)
	void DodgeInDirection(EDodgeDirection DodgeDirection);

	// equipment
	UFUNCTION()
	void CreateOrDestroyEquipmentMeshes(FItemData Newtem, bool CreateOrDestroy);
	UFUNCTION()
	void InitializeEquippedItems() {};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNiagaraComponent> BloodNiagara;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TObjectPtr<UNiagaraSystem>> BloodParticals;
	UFUNCTION()
	void DestroyNiagaraComponent(UNiagaraComponent* ComponentToDestroy);
	UFUNCTION()
	void SpawnBloodAtLocation(FVector Location);

	UFUNCTION(BlueprintCallable)
	void Die();
	UFUNCTION(BlueprintCallable)
	void BecomeDisabled();
protected:

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* Input) override;
	struct FEnhancedInputActionValueBinding* MoveActionBinding;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMontageManagerComponent* MontageManagerComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCharacterStateComponent* CharacterStateComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWeaponCollisionComponent* WeaponCollisionComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBaseCmbatComponent* CombatComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UEquipmentComponent* EquipmentComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCharacterStatusComponent* CharacterStatusComponent;

	// equipment

	UFUNCTION(BlueprintCallable)
	void EquipItem(FItemData Item);
	UFUNCTION(BlueprintCallable)
	// TODO picking up stuff off the ground
	void EquipPickUp(FItemData Item, UStaticMesh* ItemStaticMesh, USkeletalMesh* ItemSkeletalMesh) {};
	UFUNCTION(BlueprintCallable)
	void UnequipItem(FItemData Item);
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FGuid, UStaticMeshComponent*> EquipmentMeshes;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FGuid, USkeletalMeshComponent*> EquipmentSKMeshes;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<EBodyPart, FCoalatedProtectionMap> BodyPartProtectionMap;

	// weapon collision
	UFUNCTION()
	void OnValidHit(AActor* HitActor, FHitTraceResults HitResults);
	UFUNCTION()
	FFinishedAttackStruct MakeAttack(FHitTraceResults HitTraceResults);
	UFUNCTION()
	ECombatPosition AdjustCombatPosition(ECombatPosition CurrentPosition);


public:
	// interfaces

	void SetCharacterGeneralState(EGeneralState NewState);
	void SetCharacterCombatState(ECombatState NewState);

	virtual USkinnedMeshComponent* GetSkinnedMesh() override;
	virtual bool IsDead() override;
	virtual bool RecieveAttack(FFinishedAttackStruct AttackData) override;
	virtual void InterfaceSetCombatPosition_Implementation(ECombatPosition NewPosition) override {};
	virtual void InterfaceToggleWeaponCollision_Implementation(bool State) override {};
	virtual bool BreakHitStun_Implementation() override { return false; };
};
