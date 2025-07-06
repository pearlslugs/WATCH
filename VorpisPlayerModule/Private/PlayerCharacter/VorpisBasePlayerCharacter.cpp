// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter/VorpisBasePlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "AlsCharacterMovementComponent.h"
#include "Player/VorpisPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "PlayerDialogue/PlayerDialogueComponent.h"
#include "DialogueData/DialogueDataAsset.h"
#include "Kismet/KismetMathLibrary.h"
#include "ItemData/ItemEnums.h"
#include "CharacterStateData/CharacterStateEnums.h"


AVorpisBasePlayerCharacter::AVorpisBasePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;	
	InteractorComponent = CreateDefaultSubobject<UInteractorComponent>(TEXT("InteractorComponent"));
	LockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockOnComponent"));
	UncursedInputBufferComponent = CreateDefaultSubobject<UVorpisUncursedInputBufferComponent>(TEXT("InputBufferComponent"));
	PlayerDialogueComponent = CreateDefaultSubobject<UPlayerDialogueComponent>(TEXT("PlayerDialogueComponent"));
	LeftShoulderTraceLocation = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftShoulderTraceLocation"));
}

void AVorpisBasePlayerCharacter::ClearRotationReagedDelegate()
{
	OnRotationReached.Clear();
}

void AVorpisBasePlayerCharacter::SetRotationTarget(FVector NewTargetLocation)
{
	RotateTargetLocation = NewTargetLocation;
	RotationTarget =  UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), NewTargetLocation);
}

void AVorpisBasePlayerCharacter::RotateToTarget()
{
	if (FGeneralUtils::GetRotatorsNearlyMatch(RotationTarget, PlayerController->GetControlRotation())) {
		GetWorldTimerManager().ClearTimer(RotateToTargetTimer);
		OnRotationReached.Broadcast();
		EnableHandIK.Broadcast(EHandIkState::EHIS_Both);
		AVorpisBasePlayerCharacter::ClearRotationReagedDelegate();
		return;
	}
	FRotator LerpRotation = UKismetMathLibrary::RInterpTo(PlayerController->GetControlRotation(), RotationTarget, 0.01f, 45.f);
	PlayerController->SetControlRotation(LerpRotation);
	GetWorldTimerManager().SetTimer(RotateToTargetTimer, this, &AVorpisBasePlayerCharacter::RotateToTarget, RotateToTargetTime, false);
}

void AVorpisBasePlayerCharacter::SetMovementTarget()
{
	FVector InteractableLocation = InteractorComponent->GetCurrentInteractable()->GetActorLocation();
	FRotator DesiredRotation = UKismetMathLibrary::FindLookAtRotation(InteractableLocation, GetActorLocation());
	SetRotationTarget(InteractableLocation + FVector(0, 0, RotationTargetZOffset));
	SetMovementTargetLocation(InteractableLocation + DesiredRotation.Vector() * DistanceToMoveFromTarget);
	SetDesiredStance(AlsStanceTags::Crouching);
	AVorpisBasePlayerCharacter::RotateToTarget();
}
void AVorpisBasePlayerCharacter::SetIKTargetFromActor(AActor* TargetActor)
{
	if (!IsValid(TargetActor)) return;
	FVector Direction = (TargetActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	float Distance = TargetActor->GetDistanceTo(this);
	FVector DesiredRightHandPosition = TargetActor->GetActorLocation() + (Direction * (Distance * -0.25f));
	SetRightHandTargetVector(DesiredRightHandPosition + FVector(0,0, 50));
}


void AVorpisBasePlayerCharacter::BeginHarvestingFuelPlant()
{
	// this will probbly just bind a function to the rotate delagate so that the character will rotate then start the ik hand stuffS
	if (InteractorComponent->GetCurrentInteractable()) {
		InteractorComponent->SetCheckForInteractable(false);
		OnRotationReached.Clear();
		OnRotationReached.AddDynamic(this, &AVorpisBasePlayerCharacter::HarvestFuelPlant);
		CharacterStateComponent->SetCharacterGeneralState(EGeneralState::EGS_IKTask);
	}
}

void AVorpisBasePlayerCharacter::AttachScrewToFruit()
{
	if (IsValid(EquipmentComponent->GetRightHandItem().ItemAsset) && IsValid(InteractorComponent->GetCurrentInteractable()))
	{
		UStaticMeshComponent* ScrewMesh = EquipmentMeshes.FindRef(EquipmentComponent->GetRightHandItem().ItemGuid);
		if (ScrewMesh)
		{
			ScrewMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		}
	}
}

void AVorpisBasePlayerCharacter::StartHarvestingFuelPlant_Implementation(AActor* PlantActor)
{
	AVorpisBasePlayerCharacter::BeginHarvestingFuelPlant();
}

void AVorpisBasePlayerCharacter::HarvestFuelPlant()
{
	// here is where we start the mini game i guess or whatever
	// maybe we dont need it idk
}

void AVorpisBasePlayerCharacter::StartPickingUpItem()
{
	UAnimMontage* PickUpMontage = MontageManagerComponent->GetPickUpMontage(ItemToPickUp.ItemAsset->EquipmentSlot);
	if (IsValid(PickUpMontage)) {
		PlayAnimMontage(PickUpMontage);
		InteractorComponent->SetCheckForInteractable(false);
	}
}

void AVorpisBasePlayerCharacter::TaskPrimaryAction(const FInputActionValue& ActionValue)
{
	bool InputBool = ActionValue.Get<bool>();
	if (CharacterStateComponent->GetCharacterGeneralState() == EGeneralState::EGS_IKTask)
	{
		PerformPrimaryTaskAction(InputBool);
	}
}
void AVorpisBasePlayerCharacter::TaskSecondaryAction(const FInputActionValue& ActionValue)
{
	bool InputBool = ActionValue.Get<bool>();
	if (CharacterStateComponent->GetCharacterGeneralState() == EGeneralState::EGS_IKTask)
	{
		PerformSecondaryTaskAction(InputBool);
	}
}

void AVorpisBasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
	Super::SetupPlayerInputComponent(Input);
	auto* EnhancedInput{ Cast<UEnhancedInputComponent>(Input) };
	if (IsValid(EnhancedInput)) 
	{
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::MoveAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::Input_OnMove);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::LookMouseAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::Input_OnLookMouse);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::LookAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::Input_OnLook);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::JumpAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::BufferJump);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::InteractAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::CallInteract);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::DodgeAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::BufferDodge);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::KickAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::BufferKick);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::PrimaryAttackAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::BufferPrimaryAttack);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::LockOnAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::LockOn);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::MenuSelectAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::SelectInMenu);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::RightHandTaskPrimaryAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::TaskPrimaryAction);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::RightHandTaskSecondaryAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::TaskSecondaryAction);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::MashTaskInput, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::MashTaskAction);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::LeftHandToolSecondaryAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::BufferLeftHandSecondaryUse);
		// we want to bind input_onmove here so that we can use the left movement input to move the left hand
		MoveActionBinding = &EnhancedInput->BindActionValue(MoveAction);
	}
}

void AVorpisBasePlayerCharacter::AssessMashingProgress()
{
	if (MashProgress + (MashProgress / 2) > MashTime)
	{
		MashTime = MashTime + MashTimeIncimentTimerValue;
	}
	MashProgress = FMath::Clamp((MashProgress - ProgressLossDecriment), -0.1f, 0.2f);
	if (MashProgress > 0.0) {
		MashOutput = FMath::Clamp((MashOutput + 0.01), -0.3f, 1.3f);
	}
	if (MashProgress < 0.0) {
		MashOutput = FMath::Clamp((MashOutput - 0.01), -0.3f, 1.3f);
	}
}
void AVorpisBasePlayerCharacter::StopMashTask()
{
	GetWorldTimerManager().PauseTimer(MashProgressChecker);
	SetInMashTask(false);
}

void AVorpisBasePlayerCharacter::StartCheckingMashProgress()
{
	GetWorldTimerManager().SetTimer(MashProgressChecker, this, &AVorpisBasePlayerCharacter::AssessMashingProgress, MashProgressCheckerTime, true);
}
void AVorpisBasePlayerCharacter::MashTaskAction()
{
	if (CharacterStateComponent->GetCharacterGeneralState() == EGeneralState::EGS_IKTask && InMashTask)
	{
		MashProgress = FMath::Clamp((MashProgress + MashProgressIncrimentValue), -0.1f, 0.2f);
	}
}

void AVorpisBasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetViewMode(AlsViewModeTags::FirstPerson);

	//locations
	LeftShoulderTraceLocation->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale);

	// Player Controller
	PlayerController = Cast<AVorpisPlayerController>(GetController());
	
	// Lock on component
	LockOnComponent->InitializeLockOnComponent(PlayerController->PlayerCameraManager, PlayerController, this);
	LockOnComponent->OnLockedOn.AddDynamic(this, &AVorpisBasePlayerCharacter::OnLockedOn);

	// input buffer component
	UncursedInputBufferComponent->OnBufferConsumed.AddDynamic(this, &AVorpisBasePlayerCharacter::OnInputConsumed);

	// montage manager
	MontageManagerComponent->OnComboFinished.AddDynamic(this, &AVorpisBasePlayerCharacter::OnComboFinished);

	// dialogue
	//PlayerDialogueComponent->OnDialogueEnd.AddDynamic(this, &AVorpisBasePlayerCharacter::ResetState);

}
void AVorpisBasePlayerCharacter::BufferDodge() { InputBufferKey(EBufferKey::EBK_Dodge); }
void AVorpisBasePlayerCharacter::BufferLeftHandSecondaryUse()
{
	if (IsValid(EquipmentComponent->GetLeftHandItem().ItemAsset))
	{
		InputBufferKey(EBufferKey::EBK_LeftHandSecondaryAction);
	}
}
void AVorpisBasePlayerCharacter::BufferPrimaryAttack() { 
	if (IsValid(EquipmentComponent->GetRightHandItem().ItemAsset)) {
		if (EquipmentComponent->GetRightHandItem().ItemAsset->CanAttack) {
			InputBufferKey(EBufferKey::EBK_PrimaryAttack);
		}
		else {
			// try to use item on hovered thing
		}
	}
	else {
		// punch
	}
}
void AVorpisBasePlayerCharacter::BufferJump(const FInputActionValue& ActionValue) {
	if (CharacterStateComponent->GetCharacterGeneralState() == EGeneralState::EGS_InConversation) return;
	if (AVorpisBasePlayerCharacter::IsDoingTask())
	{
		return;
	}
	bool ShouldJump = ActionValue.Get<bool>();
	if (ShouldJump) {
		if (!LockOnComponent->GetIsLockedOn() && CharacterStateComponent->GetCharacterCombatState() != ECombatState::ECS_Attacking) {
			InputBufferKey(EBufferKey::EBK_Jump);
			GetWorldTimerManager().SetTimer(ResetBufferTimer, this, &AVorpisBasePlayerCharacter::ResetInputBuffer, ResetInputBufferTime, false);
			return;
		}
	} else {
		StopJumping();
	}
}
void AVorpisBasePlayerCharacter::BufferKick() { 
	if (LockOnComponent->GetIsLockedOn()) {
		InputBufferKey(EBufferKey::EBK_Kick);
	}
}


EGeneralState AVorpisBasePlayerCharacter::GetCharacterGeneralState() { return CharacterStateComponent->GetCharacterGeneralState(); }
bool AVorpisBasePlayerCharacter::IsDoingTask()
{
	return GetCharacterGeneralState() == EGeneralState::EGS_IKTask;
}

void AVorpisBasePlayerCharacter::Input_OnMove(const FInputActionValue& ActionValue)
{
	if (AVorpisBasePlayerCharacter::IsDoingTask())
	{
		// move left hand if possible
		return;
	}
	Super::Input_OnMove(ActionValue);

}

void AVorpisBasePlayerCharacter::MoveRightHand(FVector2D Input, bool UseMouse)
{
	int XInput = UseMouse ? Input.X : -Input.X;
	FVector RightMovement = GetActorRightVector() * XInput;
	FVector UpMovement = GetActorUpVector() * Input.Y;
	RightHandTargetVector += (RightMovement + UpMovement);
}

void AVorpisBasePlayerCharacter::Input_OnLook(const FInputActionValue& ActionValue)
{
	if (DisableLookControls) return;
	FVector2D Input = ActionValue.Get<FVector2D>();
	if (AVorpisBasePlayerCharacter::IsDoingTask())
	{
		if (CharacterStateComponent->GetTaskState() == ETaskState::ETS_HarvestFuelPlant && (CharacterStateComponent->GetTaskStep() == 1 ||
			CharacterStateComponent->GetTaskStep() == 2 || CharacterStateComponent->GetTaskStep() == 3))
		{
			return;
			//if (TwistScrewActive) 
		//	{
		//		return;
		//	}
		}
		if (FuelPlantPickedUp && CharacterStateComponent->GetTaskStep() == 3)
		{
			PourPlantInToContainer(Input, false);
			return;
		}
		MoveRightHand(Input, false);
		return;
	}
	if (LockOnComponent->GetIsLockedOn()) {
		CombatComponent->SetCombatPosition(CombatComponent->GetCombatPositionFromVector2D(Input));
	}
	else {
		Super::Input_OnLook(ActionValue);
	}

}
void AVorpisBasePlayerCharacter::Input_OnLookMouse(const FInputActionValue& ActionValue)
{
	if (DisableLookControls) return;
	FVector2D MouseInput = ActionValue.Get<FVector2D>();
	if (AVorpisBasePlayerCharacter::IsDoingTask())
	{
		if (CharacterStateComponent->GetTaskState() == ETaskState::ETS_HarvestFuelPlant && (CharacterStateComponent->GetTaskStep() == 1 || CharacterStateComponent->GetTaskStep() == 2))
		{
			return;
			//if (TwistScrewActive) 
		//	{
		//		return;
		//	}
		}
		if (FuelPlantPickedUp && CharacterStateComponent->GetTaskStep() == 3)
		{
			PourPlantInToContainer(MouseInput, true);
			return;
		}
		MoveRightHand(MouseInput, true);
		return;
	}
	if (LockOnComponent->GetIsLockedOn()) {
		CombatComponent->SetCombatPosition(CombatComponent->GetCombatPositionFromVector2D(MouseInput));
	}
	else {
		Super::Input_OnLookMouse(ActionValue);
	}
}
void AVorpisBasePlayerCharacter::MoveRightHandIKTarget(FVector2D Vector)
{
	// move on x
	if (RightHandIKTargetCurrentX + Vector.X < IKTargetMaxX && RightHandIKTargetCurrentX + Vector.X < IKTargetMinX) {
		FVector RightVector = GetActorRightVector() * IKTargetMovementSale * Vector.X;
		RightHandTargetVector += RightVector;
	}

	// move on y
	if (RightHandIKTargetCurrentY + Vector.Y < IKTargetMaxY && RightHandIKTargetCurrentY + Vector.Y < IKTargetMinY) {
		FVector UpVector = GetActorUpVector() * IKTargetMovementSale * Vector.Y;
		RightHandTargetVector += UpVector;
	}

}


void AVorpisBasePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Lock on component
}

void AVorpisBasePlayerCharacter::InputBufferKey(EBufferKey Key)
{
	UncursedInputBufferComponent->AcceptKey(Key);
}

void AVorpisBasePlayerCharacter::Dodge()
{
	if (LockOnComponent->GetIsLockedOn()) {
		AVorpisBasePlayerCharacter::BaseDodge();
	} else {
		static constexpr auto PlayRate{ 1.3f };
		StartRolling(PlayRate);
	}
}

void AVorpisBasePlayerCharacter::OnLockedOn(bool IsLockedOn)
{
	if (IsLockedOn) {
		SetViewMode(AlsViewModeTags::ThirdPerson);
		bUseControllerRotationYaw = true;
		AlsCharacterMovement->SetMaxAllowedGait(AlsGaitTags::Walking);
		SetLockedOnLocomotion(true);
		if (CombatComponent->GetCombatPosition() == ECombatPosition::ECP_None) {
			CombatComponent->SetCombatPosition(ECombatPosition::ECP_Right);
		}
		SetDesiredGait(AlsGaitTags::Walking);
	}
	else {
		SetViewMode(AlsViewModeTags::FirstPerson);
		bUseControllerRotationYaw = false;
		AlsCharacterMovement->SetMaxAllowedGait(AlsGaitTags::Sprinting);
		SetLockedOnLocomotion(false);
		SetDesiredGait(AlsGaitTags::Running);
	}
}

void AVorpisBasePlayerCharacter::LockOn(const FInputActionValue& ActionValue) 
{
	bool ShouldLockOn = ActionValue.Get<bool>();
	LockOnComponent->LockOn(ShouldLockOn);
}

void AVorpisBasePlayerCharacter::OnComboFinished() 
{
	CombatComponent->ResetCombo();
}

void AVorpisBasePlayerCharacter::PrimaryAttack()
{
	int Combo = 0;
	if (IsValid(LockOnComponent->TargetedActor))
	{
		IBaseRpgCharacterInterface* InterfaceActor = Cast<IBaseRpgCharacterInterface>(LockOnComponent->TargetedActor);
			if (InterfaceActor)
			{
				InterfaceActor->RecieveAttackSignal();
			}
	}
	else {
		// get sphere sweep and send like that
	}
	ECombatPosition Position = CombatComponent->GetCombatPosition();
		if (Position == ECombatPosition::ECP_High || Position == ECombatPosition::ECP_Low) {
			Combo = CombatComponent->GetComboCount();
		}
	UAnimMontage* Montage = MontageManagerComponent->GetAttackMontage(Position, false, Combo);
	if (IsValid(Montage)) {
		PlayAnimMontage(Montage);
		CombatComponent->IncrimentComboCount();
	}
}

void AVorpisBasePlayerCharacter::Kick()
{
	if (CharacterStateComponent->GetCharacterGeneralState() == EGeneralState::EGS_Combat) {
		// get kick montage form montag manager
	}
}

void AVorpisBasePlayerCharacter::ResetInputBuffer()
{
	UncursedInputBufferComponent->ResetBuffer();
}

void AVorpisBasePlayerCharacter::OnInputConsumed(EBufferKey Key)
{
	switch (Key) {
	case EBufferKey::EBK_Dodge:
		AVorpisBasePlayerCharacter::Dodge();
		break;
	case EBufferKey::EBK_PrimaryAttack:
		AVorpisBasePlayerCharacter::PrimaryAttack();
		break;
	case EBufferKey::EBK_Kick:
		AVorpisBasePlayerCharacter::Kick();
		break;
	case EBufferKey::EBK_Jump:	
		StartJumping();
		break;
	case EBufferKey::EBK_LeftHandSecondaryAction:
		PerformLeftHandSecondaryAction();
		break;
	}
}

void AVorpisBasePlayerCharacter::CallInteract()
{
	if (CharacterStateComponent->GetCharacterGeneralState() == EGeneralState::EGS_IKTask)
	{
		return;
	}
	if (IsValid(InteractorComponent->CurrentInteractable)) {
		InteractorComponent->Interact();
	}
}
void AVorpisBasePlayerCharacter::PerformLeftHandSecondaryAction()
{
	if (EquipmentComponent->GetLeftHandItem().ItemAsset->IsTool)
	{
		if (IsValid(EquipmentComponent->GetLeftHandItem().ItemAsset->SecondaryUseAnimation))
		{
			PlayAnimMontage(EquipmentComponent->GetLeftHandItem().ItemAsset->SecondaryUseAnimation);
		}
	}
}


void AVorpisBasePlayerCharacter::MountDialogueComponentAndSetAsset_Implementation(UDialogueDataAsset* AssetToMount, UUserWidget* Widget)
{
	PlayerDialogueComponent->SetDialogueAsset(AssetToMount);
	CharacterStateComponent->SetCharacterGeneralState(EGeneralState::EGS_InConversation);
	PlayerController->SetMountedComponent(PlayerDialogueComponent);
	PlayerDialogueComponent->SetMountedWidget(Widget);
	
}

void AVorpisBasePlayerCharacter::ResetState()
{
	CharacterStateComponent->SetCharacterGeneralState(EGeneralState::EGS_None);
	CharacterStateComponent->SetCharacterCombatState(ECombatState::ECS_None);
}

void AVorpisBasePlayerCharacter::MountNewDialogue(UDialogueDataAsset* AssetToMount, UUserWidget* Widget)
{
	PlayerDialogueComponent->SetDialogueAsset(AssetToMount);
	CharacterStateComponent->SetCharacterGeneralState(EGeneralState::EGS_InConversation);
	PlayerController->SetMountedComponent(PlayerDialogueComponent);
	PlayerDialogueComponent->SetMountedWidget(Widget);
}

void AVorpisBasePlayerCharacter::SelectInMenu()
{
	if (CharacterStateComponent->GetCharacterGeneralState() == EGeneralState::EGS_InConversation) 
	{
		PlayerDialogueComponent->GoToNextDialogueOption(FGuid());
	}
}

bool AVorpisBasePlayerCharacter::CheckToolProperties_Implementation(const TMap<EToolProperties, int32>& RequiredTools)
{
	FToolCompareType Results = EquipmentComponent->CompareToolCapabilities(RequiredTools);
	return Results.Success;
}

TArray<FItemData> AVorpisBasePlayerCharacter::GetEquippedItems_Implementation()
{
	return EquipmentComponent->GetQuickslotsArray();
}

void AVorpisBasePlayerCharacter::FinishPickingUpItem_Implementation(bool RightHand)
{
	EquipmentComponent->PickUpItem(GetItemToPickUp(), RightHand);
}

void AVorpisBasePlayerCharacter::DropItem_Implementation(bool RightHand)
{
	if (RightHand)
	{
		FGuid ItemGuid = EquipmentComponent->GetRightHandItem().ItemGuid;
		UStaticMeshComponent* CurrentMesh = EquipmentMeshes.FindRef(ItemGuid);
		if (CurrentMesh && IsValid(EquipmentComponent->GetRightHandItem().ItemAsset))
		{
			FTransform ItemTransform = GetMesh()->GetSocketTransform(EquipmentComponent->GetRightHandItem().ItemAsset->GetEquipSocketName());
			SpawnPickup(EquipmentComponent->GetRightHandItem(), ItemTransform);
			CurrentMesh->DestroyComponent();
			EquipmentMeshes.Remove(ItemGuid);
			EquipmentComponent->SetRightHandItem(FItemData(), true);
		}
	}
	else 
	{
		FGuid ItemGuid = EquipmentComponent->GetLeftHandItem().ItemGuid;
		UStaticMeshComponent* CurrentMesh = EquipmentMeshes.FindRef(ItemGuid);
		if (CurrentMesh && IsValid(EquipmentComponent->GetLeftHandItem().ItemAsset))
		{
			FTransform ItemTransform = GetMesh()->GetSocketTransform(EquipmentComponent->GetLeftHandItem().ItemAsset->GetEquipSocketName());
			SpawnPickup(EquipmentComponent->GetLeftHandItem(), ItemTransform);
			CurrentMesh->DestroyComponent();
			EquipmentMeshes.Remove(ItemGuid);
			EquipmentComponent->SetLeftHandItem(FItemData(), true);
		}
	}
	OnUpdateOverlay.Broadcast();
}

// blueprint implementable interfaces
void AVorpisBasePlayerCharacter::CloseInputBuffer_Implementation(){}
void AVorpisBasePlayerCharacter::OpenInputBuffer_Implementation(){}
void AVorpisBasePlayerCharacter::InterfaceSetCharacterGeneralState_Implementation(EGeneralState NewState){SetCharacterGeneralState(NewState);}
void AVorpisBasePlayerCharacter::InterfaceSetCharacterCombatState_Implementation(ECombatState NewState){SetCharacterCombatState(NewState);}
void AVorpisBasePlayerCharacter::RotateTowardsTarget_Implementation(bool State){}
void AVorpisBasePlayerCharacter::ToggleSelectedEquipmentEquipped_Implementation(bool State){}
void AVorpisBasePlayerCharacter::InterfacePopulateInitialAttackData_Implementation(FInitialAttackData InitialAttackData){}

