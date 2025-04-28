// Fill out your copyright notice in the Description page of Project Settings.


#include "RpgCharacter/BaseRpgCharacter.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/ItemDataAsset.h"
#include "NiagaraComponent.h"
#include "GeneralData/GeneralData.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
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
	CharacterStatusComponent = CreateDefaultSubobject<UCharacterStatusComponent>(TEXT("CharacterStatusComponent"));
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
	if (Item.ItemAsset->IsWeildable) {
		FName EquipSocket = Item.ItemAsset->GetEquipSocketName();
		if (!Item.ItemAsset->UseSkeletalMesh) {
			UStaticMeshComponent* EquipmentMesh = EquipmentMeshes.FindRef(Item.ItemGuid);
			if (IsValid(EquipmentMesh) && EquipSocket != FName("null")) {
				EquipmentMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, EquipSocket);
				EquipmentComponent->EquipItem(Item, Item.ItemAsset->EquipmentSlot);
				if (Item.ItemAsset->IsWeildable) {
					WeaponCollisionComponent->SetItemStaticMesh(EquipmentMesh);
				}
				return;
			}
			else if (EquipSocket == FName("null")) {
				EquipmentMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale);
			}
		}
		else {
			// this wont work, if its weildable, it already has a mesh
			USkeletalMeshComponent* EquipmentSKMesh = EquipmentSKMeshes.FindRef(Item.ItemGuid);
			if (IsValid(EquipmentSKMesh) && EquipSocket != FName("null")) {
				EquipmentSKMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, EquipSocket);
				EquipmentComponent->EquipItem(Item, Item.ItemAsset->EquipmentSlot);
				if (Item.ItemAsset->IsWeildable) {
					WeaponCollisionComponent->SetItemSkeletalMesh(EquipmentSKMesh);
				}
				return;
			}
			else if (EquipSocket == FName("null")) {
				EquipmentSKMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale);
			}
		}
	}
	else if (Item.ItemAsset->IsWearable) {
		if (Item.ItemAsset->UseSkeletalMesh) {
			FTransform AdjustedTransform;
			AdjustedTransform.SetLocation(FVector(0.f, 0.f, -92.f));
			UActorComponent* NewMeshComp = AddComponentByClass(USkeletalMeshComponent::StaticClass(), false, AdjustedTransform, false);
			USkeletalMeshComponent* EquipmentSKMesh = Cast<USkeletalMeshComponent>(NewMeshComp);
			EquipmentSKMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			EquipmentSKMesh->AddLocalRotation(FRotator(0, -90, 0));
			if (Item.ItemAsset->SkeletalMeshes.Num() > 0) {
				USkeletalMesh* NewMesh = Item.ItemAsset->SkeletalMeshes[0];
				EquipmentSKMesh->SetSkeletalMesh(Item.ItemAsset->SkeletalMeshes[0]);
				EquipmentSKMesh->SetLeaderPoseComponent(GetMesh());
				EquipmentSKMeshes.Add(Item.ItemGuid, EquipmentSKMesh);
			}
			TArray<EBodyPart> BodyParts = FGeneralUtils::EquipmentSlotToBodyPart(Item.ItemAsset->EquipmentSlot);
			EquipmentComponent->EquipItem(Item, Item.ItemAsset->EquipmentSlot);
			for (EBodyPart Part : BodyParts) {
				FCoalatedProtectionMap NewMap = FCoalatedProtectionMap();
				NewMap.InitializeMap();
				if (BodyPartProtectionMap.Contains(Part)) {
					TMap<EPhysicalDamageType, int> CurrentProtectionMap = BodyPartProtectionMap[Part].ProtectionMap;
					int TotalCoverage = BodyPartProtectionMap[Part].Coverage + Item.ItemAsset->Coverage;
					TMap<EPhysicalDamageType, int> CollatedMap = FGeneralUtils::CollateProtectionMaps(CurrentProtectionMap, Item.ItemAsset->ProtectionMap);
					NewMap.Coverage = TotalCoverage;
					NewMap.ProtectionMap = CollatedMap;
					BodyPartProtectionMap.Add(Part, NewMap);
				}
				else {
					NewMap.Coverage = Item.ItemAsset->Coverage;
					NewMap.ProtectionMap = Item.ItemAsset->ProtectionMap;
					BodyPartProtectionMap.Add(Part, NewMap);
				}
				int Coverage = BodyPartProtectionMap[Part].Coverage;
				int Blunt = BodyPartProtectionMap[Part].ProtectionMap.FindRef(EPhysicalDamageType::EPDT_Blunt);
				if (GEngine) {
					GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, "Coverage: " + FString::FromInt(Coverage));
					GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Bluntn Protection: " + FString::FromInt(Blunt));
				}
			}
		}
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

void ABaseRpgCharacter::Die()
{

}
void ABaseRpgCharacter::BecomeDisabled()
{

}

bool ABaseRpgCharacter::RecieveAttack(FFinishedAttackStruct AttackData)
{
	ECombatPosition CharacterPosition = CombatComponent->GetCombatPosition();
	ECombatPosition AdjustedPosition = ABaseRpgCharacter::AdjustCombatPosition(AttackData.AttackData.InitialAttackData.Position);
	EBodyPart HitBodyPart = FGeneralUtils::BoneToBodyPart(AttackData.HitTraceResults.HitBone);
	EPhysicalDamageType PrimaryDamageType = AttackData.PrimaryDamageType;
	float Precision = AttackData.AttackData.Precision;
	float Velocity = AttackData.AttackData.Velocity;
	float PrecisionDefense = 0.f;
	float VelocityDefense = 0.f;


	FVector AttackerLocation = AttackData.HitTraceResults.AttackerLocation;
	FVector ToAttacker = AttackerLocation - GetActorLocation();
	ToAttacker.Normalize();
	FVector Forward = GetActorForwardVector();
	float Dot = FVector::DotProduct(Forward, ToAttacker);

	bool IsBehind = Dot < 0.0f;
	if (IsBehind)
	{
		UAnimMontage* HitMontage = MontageManagerComponent->GetHitReactionMontage(AttackData.AttackData.InitialAttackData.Position, true);
		if (HitMontage) {
			CombatComponent->IncreaseHitCount();
			PlayAnimMontage(HitMontage);
			CharacterStateComponent->SetCharacterCombatState(ECombatState::ECS_HitStunned);
			ABaseRpgCharacter::SpawnBloodAtLocation(AttackData.HitTraceResults.HitLocation);
		}
	}

	if (CharacterStateComponent->GetCharacterCombatState() == ECombatState::ECS_Dodging) {
		return false;
	}

	if (AdjustedPosition == CharacterPosition) {
		// is parrying?
			// get parry reaction
		// chamber, in place dodge, ect?
		
		UAnimMontage* BlockMontage = MontageManagerComponent->GetBlockReactionMontage(CharacterPosition, false);
		if (BlockMontage) {
			CharacterStateComponent->SetCharacterCombatState(ECombatState::ECS_BlockStunned);
			PlayAnimMontage(BlockMontage);
			return false;
		} 
	} else {
		UAnimMontage* HitMontage = MontageManagerComponent->GetHitReactionMontage(AttackData.AttackData.InitialAttackData.Position);
		if (HitMontage) {

			// SAVE THIS WHEN THE ITEM IS EQUIPPED, CERTAIN SLOTS SHOULD RELATE TO BODY PARTS, DONT 
			// GET THIS EVERY TIME

			TArray<EEquipmentSlot> SelectedSlots = FGeneralUtils::BodyPartToEquipmentSlot(HitBodyPart);
			TArray<FItemData> Equipment;
			TMap<EPhysicalDamageType, int> TotalProtectionMap;
			TotalProtectionMap.Add(EPhysicalDamageType::EPDT_Blunt, 0);
			TotalProtectionMap.Add(EPhysicalDamageType::EPDT_Composure, 0);
			TotalProtectionMap.Add(EPhysicalDamageType::EPDT_Hack, 0);
			TotalProtectionMap.Add(EPhysicalDamageType::EPDT_Pierce, 0);
			TotalProtectionMap.Add(EPhysicalDamageType::EPDT_Slash, 0);

			if (BodyPartProtectionMap.Contains(HitBodyPart)) {
				TotalProtectionMap = BodyPartProtectionMap[HitBodyPart].ProtectionMap;
				VelocityDefense += TotalProtectionMap[EPhysicalDamageType::EPDT_Blunt];
				VelocityDefense += TotalProtectionMap[PrimaryDamageType];
				PrecisionDefense += BodyPartProtectionMap[HitBodyPart].Coverage;
				PrecisionDefense += TotalProtectionMap[PrimaryDamageType];
			}

			// if the roll is 1.2, we need to roll again for super crit
			// what does this do????
			float VelocityModifier = FMath::FRandRange(0.8f, 1.2f);
			bool VelocityRoll = (VelocityDefense * VelocityModifier) > Velocity;
			float PrecisionModifier = FMath::FRandRange(0.8f, 1.2f);
			bool PrecisionRoll = (PrecisionDefense * PrecisionModifier) > Precision;
			if (PrecisionRoll) {
				AttackData.AttackData.DamageMap[EPhysicalDamageType::EPDT_Hack] = AttackData.AttackData.DamageMap[EPhysicalDamageType::EPDT_Hack] / 2;
				AttackData.AttackData.DamageMap[EPhysicalDamageType::EPDT_Pierce] = AttackData.AttackData.DamageMap[EPhysicalDamageType::EPDT_Pierce] / 2;
				AttackData.AttackData.DamageMap[EPhysicalDamageType::EPDT_Slash] = AttackData.AttackData.DamageMap[EPhysicalDamageType::EPDT_Slash] / 2;
			}
			if (VelocityRoll) {
				AttackData.AttackData.DamageMap[EPhysicalDamageType::EPDT_Blunt] = AttackData.AttackData.DamageMap[EPhysicalDamageType::EPDT_Blunt] / 2;
			}
			float TotalDamage = FGeneralUtils::GetTotalDamageFromAttack(AttackData.AttackData.DamageMap, TotalProtectionMap, AttackData.PrimaryDamageType);
			//if (GEngine) {
			//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Magenta, "Total Damage: " + FString::FromInt(TotalDamage));
			//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Emerald, "Velcoity Roll: " + FString::FromInt(VelocityRoll));
			//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Cyan, "Pecision Roll: " + FString::FromInt(PrecisionRoll));
			//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Red, "VelcoityDamage: " + FString::FromInt(Velocity));
			//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::White, "Precision Defense: " + FString::FromInt(Precision));
			//}
			if (TotalDamage < 0) {
				CharacterStatusComponent->DamageBodyPart(HitBodyPart, FMath::Abs((float)TotalDamage),
					(PrimaryDamageType != EPhysicalDamageType::EPDT_Blunt) && !PrecisionRoll);
			}
			else {
				CharacterStatusComponent->DamageBodyPart(HitBodyPart, Velocity / 2, false);
			}
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
	FFinishedAttackStruct Attack = ABaseRpgCharacter::MakeAttack(HitResults);
	IBaseRpgCharacterInterface* InterfaceCharacter = Cast<IBaseRpgCharacterInterface>(HitActor);
	if (InterfaceCharacter) {
		InterfaceCharacter->RecieveAttack(Attack);
	}
}

FFinishedAttackStruct ABaseRpgCharacter::MakeAttack(FHitTraceResults TraceData)
{
	FFinishedAttackStruct Attack;
	Attack.HitTraceResults = TraceData;
	Attack.AttackData.InitialAttackData = CurrentInitialAttackData;
	Attack.AttackData.DamageMap = EquipmentComponent->GetRightHandItem().AdjustedDamageMap;
	EPhysicalDamageType DamageType = EquipmentComponent->GetRightHandItem().ItemAsset->
		SwingDamageTypeMap[(uint8)CurrentInitialAttackData.SwingType];
	Attack.PrimaryDamageType = DamageType;
	// use swing type to map the damage types
	// every attack thats a swing does all swing damage type and blunt damage type, so slash and blunt or hack and blunt or just blunt
	// every thrust does thrust damage type, so tahts essentailly either pierce and bash, but we can force it
	// bash attack does blunt x  {bash multiplier in weapon info} so it just boosts it, maybe it shoud just be additiive

	// we need to find a way to get the weapons attack type.
	// maybe a way of getting the primary or secondary attack type from the animation
	// then we need to find a way of setting and getting what the primary attack type of the weapon 
	// blunt is always applied, but weapons with a cutting type, besides hack, have a lower velocity mulitplier
	// hack gets no blunt damage, but a higher verlocity on the cut.
	float PrecisionModifier = FMath::FRandRange(0.8f, 1.2f);
	float VelocityModifier = FMath::FRandRange(0.8f, 1.2f);

	// Precision also need to account for the weapoon skill and the charactes dex. we will do something about this i guess haha
	// I guess we will add the stats component and just keep it on rails in this game without character building
	float DexScaling = 1.2f;

	if (DamageType != EPhysicalDamageType::EPDT_Blunt) {
		// if main type is not blunt, we will rely on some type of cutting or a mix for damage.
		Attack.AttackData.Precision = EquipmentComponent->GetRightHandItem().AdjustedDamageMap.FindRef(EPhysicalDamageType::EPDT_Slash) * PrecisionModifier;
		Attack.AttackData.Velocity = EquipmentComponent->GetRightHandItem().AdjustedDamageMap.FindRef(EPhysicalDamageType::EPDT_Blunt) * VelocityModifier;
	} else {
		// if main type is blunt, we want to do extra blunt damage.
		Attack.AttackData.Precision = 1.f;
		Attack.AttackData.Velocity = EquipmentComponent->GetRightHandItem().AdjustedDamageMap.FindRef(EPhysicalDamageType::EPDT_Blunt) * 2 * VelocityModifier;
	}
	CurrentAttack = Attack;
	return Attack;
}



// character state
void ABaseRpgCharacter::SetCharacterCombatState(ECombatState NewState) { CharacterStateComponent->SetCharacterCombatState(NewState); }
void ABaseRpgCharacter::SetCharacterGeneralState(EGeneralState NewState) { CharacterStateComponent->SetCharacterGeneralState(NewState); }
