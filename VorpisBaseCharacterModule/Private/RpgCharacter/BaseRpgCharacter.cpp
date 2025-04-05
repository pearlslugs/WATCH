// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgCharacter/BaseRpgCharacter.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/ItemDataAsset.h"
#include "NiagaraComponent.h"
#include "GeneralData/GeneralData.h"
#include "NiagaraFunctionLibrary.h"
#include "EnhancedInputSubsystems.h"

ABaseRpgCharacter::ABaseRpgCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CombatComponent = CreateDefaultSubobject<UBaseCmbatComponent>(TEXT("CombatComponent"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
	MontageManagerComponent = CreateDefaultSubobject<UMontageManagerComponent>(TEXT("MontageManagerComponent"));
	CharacterStateComponent = CreateDefaultSubobject<UCharacterStateComponent>(TEXT("CharacterStateComponent"));
	WeaponCollisionComponent = CreateDefaultSubobject<UWeaponCollisionComponent>(TEXT("WeaponCollisionComponent"));
}

void ABaseRpgCharacter::BeginPlay()
{
	Super::BeginPlay();
	// weapon collision
	WeaponCollisionComponent->OnWeaponHitActor.AddDynamic(this, &ABaseRpgCharacter::OnValidHit);

	// equipment
	EquipmentComponent->AffectEquipmentStaticMeshes.AddDynamic(this, &ABaseRpgCharacter::CreateOrDestroyEquipmentMeshes);
}

void ABaseRpgCharacter::EquipItem(FItemData Item)
{
	UStaticMeshComponent* EquipmentMesh = EquipmentMeshes.FindRef(Item.ItemGuid);
	if (IsValid(EquipmentMesh)) {
		EquipmentMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Item.ItemAsset->GetEquipSocketName());
		EquipmentComponent->EquipItem(Item, Item.ItemAsset->EquipmentSlot);
		if (Item.ItemAsset->IsWeildable) {
			WeaponCollisionComponent->SetItemStaticMesh(EquipmentMesh);
		}
		return;
	}
}
// move to base rpg charactr
void ABaseRpgCharacter::UnequipItem(FItemData Item)
{
	UStaticMeshComponent* EquipmentMesh = EquipmentMeshes.FindRef(Item.ItemGuid);
	if (IsValid(EquipmentMesh)) {
		EquipmentMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Item.ItemAsset->GetUnequipSocketName());
		EquipmentComponent->UnequipItem(Item.ItemAsset->EquipmentSlot);
		if (Item.ItemAsset->IsWeildable) {
			// once we have real item data, use this
			// if (Item.AdjustedDamageMap.Num() > 0) {
			WeaponCollisionComponent->SetItemStaticMesh(EquipmentMesh);
		}
	}
}

void ABaseRpgCharacter::BaseDodge()
{
	const FVector2D InputValue = MoveActionBinding->GetValue().Get<FVector2D>();
	float AbsoluteY = FMath::Abs(InputValue.Y);
	float AbsoluteX = FMath::Abs(InputValue.X);
	if (AbsoluteX < 0.1 && AbsoluteY < 0.1) {
		DodgeInDirection(EDodgeDirection::ESMD_Backward);
		return;
	}
	if (AbsoluteY > AbsoluteX) {
		if (InputValue.Y > 0) {
			DodgeInDirection(EDodgeDirection::ESMD_Forward);
			return;
		}
		else {
			DodgeInDirection(EDodgeDirection::ESMD_Backward);
			return;
		}
	}
	else {
		if (InputValue.X > 0) {
			DodgeInDirection(EDodgeDirection::ESMD_Right);
			return;
		}
		else {
			DodgeInDirection(EDodgeDirection::ESMD_Left);
			return;
		}
	}
}

void ABaseRpgCharacter::DodgeInDirection(EDodgeDirection DodgeDirection)
{
	CharacterStateComponent->SetCharacterCombatState(ECombatState::ECS_Dodging);
	UAnimMontage* DodgeMontage = MontageManagerComponent->GetDodgeMontage(DodgeDirection);
	if (IsValid(DodgeMontage)) {
		CharacterStateComponent->SetCharacterCombatState(ECombatState::ECS_Dodging);
		PlayAnimMontage(DodgeMontage);
	}
}

void ABaseRpgCharacter::CreateOrDestroyEquipmentMeshes(FItemData NewItem, bool CreateOrDestroy)
{
	if (CreateOrDestroy) {
		UActorComponent* NewMesh = AddComponentByClass(UStaticMeshComponent::StaticClass(), true, FTransform(), false);
		if (IsValid(NewMesh)) {
			UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(NewMesh);
			if (IsValid(StaticMesh)) {
				// create and attach mesh
				StaticMesh->SetStaticMesh(NewItem.ItemAsset->BaseMeshes[0]);
				StaticMesh->SetGenerateOverlapEvents(true);
				StaticMesh->SetVisibility(true);
				StaticMesh->SetRenderCustomDepth(true);
				StaticMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
				StaticMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, NewItem.ItemAsset->GetUnequipSocketName());
				EquipmentMeshes.Add(NewItem.ItemGuid, StaticMesh);
			}
		}
	}
	else {
		// destroy equipment mesh
		EquipmentMeshes.FindRef(NewItem.ItemGuid)->DestroyComponent();
		EquipmentMeshes.Remove(NewItem.ItemGuid);
	}
}

void ABaseRpgCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
	Super::SetupPlayerInputComponent(Input);
}

USkinnedMeshComponent* ABaseRpgCharacter::GetSkinnedMesh()
{
	return GetMesh();
}

bool ABaseRpgCharacter::IsDead()
{
	return false;
}


void ABaseRpgCharacter::DestroyNiagaraComponent(UNiagaraComponent* ComponentToDestroy)
{
	ComponentToDestroy->DestroyComponent();
}

void ABaseRpgCharacter::SpawnBloodAtLocation(FVector Location)
{
	UNiagaraSystem* SelectedPartical = BloodParticals[FMath::RandRange(0, BloodParticals.Num() - 1)];
	UNiagaraComponent* NewComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SelectedPartical, Location);
	NewComponent->OnSystemFinished.AddDynamic(this, &ABaseRpgCharacter::DestroyNiagaraComponent);
}

ECombatPosition ABaseRpgCharacter::AdjustCombatPosition(ECombatPosition CurrentPosition)
{
	if (CurrentPosition == ECombatPosition::ECP_High) {
		return ECombatPosition::ECP_High;
	}
	else if (CurrentPosition == ECombatPosition::ECP_Left) {
		return ECombatPosition::ECP_Right;
	}
	return ECombatPosition::ECP_Left;
}

bool ABaseRpgCharacter::RecieveAttack(FFinishedAttackStruct AttackData)
{
	ECombatPosition CharacterPosition = CombatComponent->GetCombatPosition();
	ECombatPosition AdjustedPosition = ABaseRpgCharacter::AdjustCombatPosition(AttackData.AttackData.InitialAttackData.Position);
	// instead of false, we need to  see if they have a weapon or shield to block with
	if (AdjustedPosition == CharacterPosition) {
		// is parrying?
			// get parry reaction
		// chamber, in place dodge, ect?
		if (CharacterStateComponent->GetCharacterCombatState() == ECombatState::ECS_Dodging) {
			return false;
		}
		UAnimMontage* BlockMontage = MontageManagerComponent->GetBlockReactionMontage(CharacterPosition, false);
		if (BlockMontage) {
			CharacterStateComponent->SetCharacterCombatState(ECombatState::ECS_BlockStunned);
			PlayAnimMontage(BlockMontage);
		} 
	} else {
		UAnimMontage* HitMontage = MontageManagerComponent->GetHitReactionMontage(AttackData.AttackData.InitialAttackData.Position);
		if (HitMontage) {
			CombatComponent->IncreaseHitCount();
			PlayAnimMontage(HitMontage);
			CharacterStateComponent->SetCharacterCombatState(ECombatState::ECS_HitStunned);
			ABaseRpgCharacter::SpawnBloodAtLocation(AttackData.HitTraceResults.HitLocation);
		}
	}
	return true;
}

void ABaseRpgCharacter::OnValidHit(AActor* HitActor, FHitTraceResults HitResults)
{
	ABaseRpgCharacter::MakeAttack(HitResults);
	IBaseRpgCharacterInterface* InterfaceCharacter = Cast<IBaseRpgCharacterInterface>(HitActor);
	if (InterfaceCharacter) {
		InterfaceCharacter->RecieveAttack(CurrentAttack);
	}
}

FFinishedAttackStruct ABaseRpgCharacter::MakeAttack(FHitTraceResults TraceData)
{
	FFinishedAttackStruct Attack;
	Attack.HitTraceResults = TraceData;
	Attack.AttackData.InitialAttackData = CurrentInitialAttackData;
	Attack.AttackData.Velocity = EquipmentComponent->GetRightHandItem().AdjustedDamageMap.FindRef(EPhysicalDamageType::EPDT_Blunt);
	// we need to find a way to get the weapons attack type.
	// maybe a way of getting the primary or secondary attack type from the animation
	// then we need to find a way of setting and getting what the primary attack type of the weapon 
	// blunt is always applied, but weapons with a cutting type, besides hack, have a lower velocity mulitplier
	// hack gets no blunt damage, but a higher verlocity on the cut.
	Attack.AttackData.Precision = EquipmentComponent->GetRightHandItem().AdjustedDamageMap.FindRef(EPhysicalDamageType::EPDT_Slash);
	CurrentAttack = Attack;
	return Attack;
}



// character state
void ABaseRpgCharacter::SetCharacterCombatState(ECombatState NewState) { CharacterStateComponent->SetCharacterCombatState(NewState); }
void ABaseRpgCharacter::SetCharacterGeneralState(EGeneralState NewState) { CharacterStateComponent->SetCharacterGeneralState(NewState); }
