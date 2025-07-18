// Fill out your copyright notice in the Description page of Project Settings.

#include "MontageManagerComponent/MontageManagerComponent.h"
#include "ItemData/ItemEnums.h"

// Sets default values for this component's properties
UMontageManagerComponent::UMontageManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMontageManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMontageManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UAnimMontage* UMontageManagerComponent::GetAttackMontage(ECombatPosition CombatPosition, bool UseAlternative, int Combo)
{
	if (CombatPosition == ECombatPosition::ECP_None) {
		return nullptr;
	}
	if (Combo >= CurrentCombatMontages.Montages[CombatPosition].Montages.Num()) {
		Combo = 0;
		OnComboFinished.Broadcast();
	}
	else if (Combo == CurrentCombatMontages.Montages[CombatPosition].Montages.Num() -1) {
		OnComboFinished.Broadcast();
	}
	UAnimMontage* Montage = UseAlternative ?
		CurrentCombatMontages.AlternativeMontages[CombatPosition].Montages[Combo] : 
		CurrentCombatMontages.Montages[CombatPosition].Montages[Combo];
	if (Montage) {

		return Montage;
	} else {
		return nullptr;
	}
}

UAnimMontage* UMontageManagerComponent::GetHitReactionMontage(ECombatPosition CombatPosition, bool HitFromTheBack, int SpecificReaction)
{
	if (HitFromTheBack) {
		return HitFromTheBackMontage;
	}

	int ChosenIndex = SpecificReaction == 0 ?
		FMath::RandRange(0, HitReactionMontages.Montages[CombatPosition].Montages.Num() - 1) : SpecificReaction;
	UAnimMontage* Montage = HitReactionMontages.Montages[CombatPosition].Montages[ChosenIndex];
	if (Montage) {
		return Montage;
	}
	else {
		return nullptr;
	}

}

UAnimMontage* UMontageManagerComponent::GetBlockReactionMontage(ECombatPosition CombatPosition, bool UseAlternative)
{
	int RandomIndex = FMath::RandRange(0, BlockReactionMontages.Montages[CombatPosition].Montages.Num() - 1);
	UAnimMontage* Montage = BlockReactionMontages.Montages[CombatPosition].Montages[RandomIndex];
	if (Montage) {
		return Montage;
	}
	else {
		return nullptr;
	}
}

void UMontageManagerComponent::PlaySelectedMontage(UAnimMontage* Montage)
{
	if (OwnerMesh && Montage) {
		OwnerMesh->GetAnimInstance()->Montage_Play(Montage);
	}
}

UAnimMontage* UMontageManagerComponent::GetDodgeMontage(EDodgeDirection DodgeDirection)
{
	if (DodgeMontages.Num() > 0) {
		UAnimMontage* Montage = DodgeMontages[DodgeDirection];
		if (IsValid(Montage)) {
			return Montage;
		}
	}
	return nullptr;
}

UAnimMontage* UMontageManagerComponent::GetPickUpMontage(EEquipmentSlot ItemEquipSlot)
{
	UAnimMontage* MontageToUse = nullptr;
	switch (ItemEquipSlot)
	{
	case EEquipmentSlot::EES_LeftHand:
		MontageToUse = LeftHandedPickUpMontage;
		break;
	default:
		MontageToUse = RightHandedPickUpMontage;
		break;
	}
	if (IsValid(MontageToUse)) {
		return MontageToUse;
	}
	return nullptr;
}