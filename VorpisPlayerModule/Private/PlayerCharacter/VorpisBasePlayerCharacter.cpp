// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter/VorpisBasePlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "AlsCharacterMovementComponent.h"
#include "Player/VorpisPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "PlayerDialogue/PlayerDialogueComponent.h"
#include "DialogueData/DialogueDataAsset.h"
#include "ItemData/ItemEnums.h"
#include "CharacterStateData/CharacterStateEnums.h"


AVorpisBasePlayerCharacter::AVorpisBasePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;	
	InteractorComponent = CreateDefaultSubobject<UInteractorComponent>(TEXT("InteractorComponent"));
	LockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockOnComponent"));
	UncursedInputBufferComponent = CreateDefaultSubobject<UVorpisUncursedInputBufferComponent>(TEXT("InputBufferComponent"));
	PlayerDialogueComponent = CreateDefaultSubobject<UPlayerDialogueComponent>(TEXT("PlayerDialogueComponent"));
}

void AVorpisBasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
	Super::SetupPlayerInputComponent(Input);
	auto* EnhancedInput{ Cast<UEnhancedInputComponent>(Input) };
	if (IsValid(EnhancedInput))
	{
		EnhancedInput->BindAction(LookMouseAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::Input_OnLookMouse);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::Input_OnLook);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::BufferJump);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::DodgeAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::BufferDodge);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::KickAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::BufferKick);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::PrimaryAttackAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::BufferPrimaryAttack);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::LockOnAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::LockOn);
		EnhancedInput->BindAction(AVorpisBasePlayerCharacter::MenuSelectAction, ETriggerEvent::Triggered, this, &AVorpisBasePlayerCharacter::SelectInMenu);
		MoveActionBinding = &EnhancedInput->BindActionValue(MoveAction);
	}
}

void AVorpisBasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

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
	PlayerDialogueComponent->OnDialogueEnd.AddDynamic(this, &AVorpisBasePlayerCharacter::ResetState);

}
void AVorpisBasePlayerCharacter::BufferDodge() { InputBufferKey(EBufferKey::EBK_Dodge); }
void AVorpisBasePlayerCharacter::BufferPrimaryAttack() { 
	if (IsValid(EquipmentComponent->GetRightHandItem().ItemAsset)) {
		InputBufferKey(EBufferKey::EBK_PrimaryAttack);
	}
	else {
		// punch
	}
}
void AVorpisBasePlayerCharacter::BufferJump(const FInputActionValue& ActionValue) {
	if (CharacterStateComponent->GetCharacterGeneralState() == EGeneralState::EGS_InConversation || CharacterStateComponent->GetCharacterGeneralState() == EGeneralState::EGS_FixingEquipment) return;
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

void AVorpisBasePlayerCharacter::Input_OnLookMouse(const FInputActionValue& ActionValue)
{
	if (LockOnComponent->GetIsLockedOn()) {
		FVector2D MouseInput = ActionValue.Get<FVector2D>();
		CombatComponent->SetCombatPosition(CombatComponent->GetCombatPositionFromVector2D(MouseInput));
	} else {
		Super::Input_OnLookMouse(ActionValue);
	}
}

void AVorpisBasePlayerCharacter::Input_OnLook(const FInputActionValue& ActionValue)
{
	if (LockOnComponent->GetIsLockedOn()) {
		// Lock on component
	}
	else {
		Super::Input_OnLook(ActionValue);
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
		bUseControllerRotationYaw = true;
		AlsCharacterMovement->SetMaxAllowedGait(AlsGaitTags::Walking);
		SetLockedOnLocomotion(true);
		if (CombatComponent->GetCombatPosition() == ECombatPosition::ECP_None) {
			CombatComponent->SetCombatPosition(ECombatPosition::ECP_Right);
		}
		SetDesiredGait(AlsGaitTags::Walking);
	}
	else {
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
		if (Position == ECombatPosition::ECP_High) {
			Combo = CombatComponent->GetComboCount();
		}
	UAnimMontage* Montage = MontageManagerComponent->GetAttackMontage(Position, false, Combo);
	if (IsValid(Montage)) {
		CombatComponent->IncrimentComboCount();
		PlayAnimMontage(Montage);
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

// blueprint implementable interfaces
void AVorpisBasePlayerCharacter::CloseInputBuffer_Implementation(){}
void AVorpisBasePlayerCharacter::OpenInputBuffer_Implementation(){}
void AVorpisBasePlayerCharacter::InterfaceSetCharacterGeneralState_Implementation(EGeneralState NewState){SetCharacterGeneralState(NewState);}
void AVorpisBasePlayerCharacter::InterfaceSetCharacterCombatState_Implementation(ECombatState NewState){SetCharacterCombatState(NewState);}
void AVorpisBasePlayerCharacter::RotateTowardsTarget_Implementation(bool State){}
void AVorpisBasePlayerCharacter::ToggleSelectedEquipmentEquipped_Implementation(bool State){}
void AVorpisBasePlayerCharacter::InterfacePopulateInitialAttackData_Implementation(FInitialAttackData InitialAttackData){}

