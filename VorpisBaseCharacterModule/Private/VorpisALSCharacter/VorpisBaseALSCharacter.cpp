// Fill out your copyright notice in the Description page of Project Settings.

#include "VorpisALSCharacter/VorpisBaseALSCharacter.h"
#include "AlsCameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Utility/AlsVector.h"

AVorpisBaseALSCharacter::AVorpisBaseALSCharacter()
{
	Camera = CreateDefaultSubobject<UAlsCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh());
	Camera->SetRelativeRotation_Direct({ 0.0f, 90.0f, 0.0f });
}

void AVorpisBaseALSCharacter::NotifyControllerChanged()
{
	const auto* PreviousPlayer{ Cast<APlayerController>(PreviousController) };
	if (IsValid(PreviousPlayer))
	{
		auto* EnhancedInputSubsystem{ ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PreviousPlayer->GetLocalPlayer()) };
		if (IsValid(EnhancedInputSubsystem))
		{
			EnhancedInputSubsystem->RemoveMappingContext(InputMappingContext);
		}
	}

	auto* NewPlayer{ Cast<APlayerController>(GetController()) };
	if (IsValid(NewPlayer))
	{
		NewPlayer->InputYawScale_DEPRECATED = 1.0f;
		NewPlayer->InputPitchScale_DEPRECATED = 1.0f;
		NewPlayer->InputRollScale_DEPRECATED = 1.0f;

		auto* EnhancedInputSubsystem{ ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(NewPlayer->GetLocalPlayer()) };
		if (IsValid(EnhancedInputSubsystem))
		{
			EnhancedInputSubsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	Super::NotifyControllerChanged();
}

void AVorpisBaseALSCharacter::CalcCamera(const float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	if (Camera->IsActive())
	{
		Camera->GetViewInfo(ViewInfo);
		return;
	}

	Super::CalcCamera(DeltaTime, ViewInfo);
}

void AVorpisBaseALSCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
	Super::SetupPlayerInputComponent(Input);

	auto* EnhancedInput{ Cast<UEnhancedInputComponent>(Input) };
	if (IsValid(EnhancedInput))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnMove);
		EnhancedInput->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSprint);
		EnhancedInput->BindAction(WalkAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnWalk);
		EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnCrouch);
		EnhancedInput->BindAction(AimAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnAim);
		EnhancedInput->BindAction(RagdollAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnRagdoll);
		//EnhancedInput->BindAction(RollAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnRoll);
		EnhancedInput->BindAction(RotationModeAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnRotationMode);
		EnhancedInput->BindAction(ViewModeAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnViewMode);
		EnhancedInput->BindAction(SwitchShoulderAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSwitchShoulder);
	}
}

void AVorpisBaseALSCharacter::Input_OnLookMouse(const FInputActionValue& ActionValue)
{
	const auto Value{ ActionValue.Get<FVector2D>() };

	AddControllerPitchInput(Value.Y * LookUpMouseSensitivity);
	AddControllerYawInput(Value.X * LookRightMouseSensitivity);
}

void AVorpisBaseALSCharacter::Input_OnLook(const FInputActionValue& ActionValue)
{
	const auto Value{ ActionValue.Get<FVector2D>() };

	AddControllerPitchInput(Value.Y * LookUpRate * GetWorld()->GetDeltaSeconds());
	AddControllerYawInput(Value.X * LookRightRate * GetWorld()->GetDeltaSeconds());
}

void AVorpisBaseALSCharacter::Input_OnMove(const FInputActionValue& ActionValue)
{
	if (DisableWalking)
	{

		return;
	}
	const auto Value{ UAlsVector::ClampMagnitude012D(ActionValue.Get<FVector2D>()) };

	const auto ForwardDirection{ UAlsVector::AngleToDirectionXY(UE_REAL_TO_FLOAT(GetViewState().Rotation.Yaw)) };
	const auto RightDirection{ UAlsVector::PerpendicularCounterClockwiseXY(ForwardDirection) };
	AddMovementInput(ForwardDirection * Value.Y + RightDirection * Value.X);
}

void AVorpisBaseALSCharacter::Input_OnSprint(const FInputActionValue& ActionValue)
{
	if (!LockedOnLocomotion)
	{
		SetDesiredGait(ActionValue.Get<bool>() ? AlsGaitTags::Sprinting : AlsGaitTags::Running);
	}
	else
	{
		SetDesiredGait(ActionValue.Get<bool>() ? AlsGaitTags::Running : AlsGaitTags::Walking);
	}
}

void AVorpisBaseALSCharacter::StartLockedOnLocomotion()
{
	SetDesiredGait(AlsGaitTags::Walking);
	SetIsLockedOnLocomotion(true);
}

void AVorpisBaseALSCharacter::StopLockedOnLocomotion()
{
	SetDesiredGait(AlsGaitTags::Running);
	SetIsLockedOnLocomotion(false);
}

void AVorpisBaseALSCharacter::Input_OnWalk()
{
	if (GetDesiredGait() == AlsGaitTags::Walking)
	{
		SetDesiredGait(AlsGaitTags::Running);
	}
	else if (GetDesiredGait() == AlsGaitTags::Running)
	{
		SetDesiredGait(AlsGaitTags::Walking);
	}
}

void AVorpisBaseALSCharacter::Input_OnCrouch()
{
	if (GetDesiredStance() == AlsStanceTags::Standing)
	{
		SetDesiredStance(AlsStanceTags::Crouching);
	}
	else if (GetDesiredStance() == AlsStanceTags::Crouching)
	{
		SetDesiredStance(AlsStanceTags::Standing);
	}
}

void AVorpisBaseALSCharacter::Input_OnJump(const FInputActionValue& ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		if (StopRagdolling())
		{
			StopAnimMontage();
			return;
		}

		//if (TryStartMantlingGrounded())
		//{
		//	return;
		//}

		if (GetStance() == AlsStanceTags::Crouching)
		{
			SetDesiredStance(AlsStanceTags::Standing);
			return;
		}

		Jump();
	}
	else
	{
		StopJumping();
	}
}

void AVorpisBaseALSCharacter::Input_OnAim(const FInputActionValue& ActionValue)
{
	SetDesiredAiming(ActionValue.Get<bool>());
}

void AVorpisBaseALSCharacter::Input_OnRagdoll()
{
	if (!StopRagdolling())
	{
		StartRagdolling();
	}
}

void AVorpisBaseALSCharacter::Input_OnRoll()
{
	static constexpr auto PlayRate{ 1.3f };

	StartRolling(PlayRate);
}

void AVorpisBaseALSCharacter::Input_OnRotationMode()
{
	SetDesiredRotationMode(GetDesiredRotationMode() == AlsRotationModeTags::VelocityDirection
		? AlsRotationModeTags::ViewDirection
		: AlsRotationModeTags::VelocityDirection);
}

void AVorpisBaseALSCharacter::Input_OnViewMode()
{
	SetViewMode(GetViewMode() == AlsViewModeTags::ThirdPerson ? AlsViewModeTags::FirstPerson : AlsViewModeTags::ThirdPerson);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AVorpisBaseALSCharacter::Input_OnSwitchShoulder()
{
	Camera->SetRightShoulder(!Camera->IsRightShoulder());
}

void AVorpisBaseALSCharacter::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& Unused, float& VerticalLocation)
{
	if (Camera->IsActive())
	{
		Camera->DisplayDebug(Canvas, DebugDisplay, VerticalLocation);
	}

	Super::DisplayDebug(Canvas, DebugDisplay, Unused, VerticalLocation);
}


void AVorpisBaseALSCharacter::StartJumping()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
	{
		GetMesh()->GetAnimInstance()->Montage_Stop(0.1f);
		GetWorldTimerManager().SetTimer(DelayJumpTimer, this, &AVorpisBaseALSCharacter::StartJumping, 0.1f, false);
		return;
	}
	if (StopRagdolling())
	{
		return;
	}

	//if (TryStartMantlingGrounded())
	//{
	//	return;
	//}

	if (GetStance() == AlsStanceTags::Crouching)
	{
		SetDesiredStance(AlsStanceTags::Standing);
		return;
	}
	Jump();
}