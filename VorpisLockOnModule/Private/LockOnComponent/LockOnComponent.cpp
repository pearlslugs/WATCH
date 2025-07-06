// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnComponent/LockOnComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "BaseInterface/BaseRpgCharacterInterface.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CharacterOwner = GetOwner();

	// ...
	
}

// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULockOnComponent::InitializeLockOnComponent(APlayerCameraManager* CameraManager, APlayerController* NewPlayerController, AActor* NewCharacterOwner)
{
	PlayerCameraManager = CameraManager;
	PlayerController = NewPlayerController;
	CharacterOwner = NewCharacterOwner;
	ContinueLockingOn.BindUFunction(this, FName("ContinuousLockOn"));
}	


void ULockOnComponent::ContinuousLockOn()
{
	if (PlayerController && IsValid(TargetedActor) && (CharacterOwner->GetActorLocation() - TargetedActor->GetActorLocation()).Size() > 90.f)
	{
		FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
		FVector CameraForward = PlayerCameraManager->GetCameraRotation().Vector();
		FRotator CurrentCameraRotation = PlayerController->GetControlRotation();
		FRotator DesiredRotation = UKismetMathLibrary::FindLookAtRotation(CameraLocation, TargetedActor->GetActorLocation());
		UKismetMathLibrary::RInterpTo(CurrentCameraRotation, DesiredRotation, 0.025f, 8);
		FRotator NewRotator = FRotator(FMath::Clamp(DesiredRotation.Pitch, -10, -10), DesiredRotation.Yaw, CurrentCameraRotation.Roll);
		PlayerController->SetControlRotation(NewRotator);
	}
}

bool ULockOnComponent::FindClosestActor()
{
	FVector OwnerLocation = CharacterOwner->GetActorLocation();
	FVector PotentialTargetLocation;
	float ClosestTargetDistance = 99000.f;
	AActor* CurrentClosestActor = nullptr;

	for (auto Target : PotentialTargets)
	{
		IBaseRpgCharacterInterface* InterfaceCharacter = Cast<IBaseRpgCharacterInterface>(Target);
		PotentialTargetLocation = Target->GetActorLocation();
		if ((PotentialTargetLocation - OwnerLocation).Size() < ClosestTargetDistance && !InterfaceCharacter->IsDead())
		{
			ClosestTargetDistance = (PotentialTargetLocation - OwnerLocation).Size();
			CurrentClosestActor = Target;
		}
	}
	if (CurrentClosestActor)
	{
		TargetedActor = CurrentClosestActor;
		return true;
	}
	return false;
}

void ULockOnComponent::LockOn(bool LockOn)
{
	IsLockedOn = LockOn;
	if (IsTargeting || !LockOn)
	{
		ULockOnComponent::StopTargeting();
	}
	else
	{
		TArray<AActor*> HitCharacters;
		TArray<FHitResult> HitResults;
		FCollisionShape TraceSphere = FCollisionShape::MakeSphere(1500.0f);
		GetWorld()->SweepMultiByChannel(HitResults, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + FVector(0,0,2), FQuat::Identity, ECC_Pawn, TraceSphere);
		for (auto& HitResult : HitResults) {
			if (HitResult.GetActor() == CharacterOwner) continue;
			IBaseRpgCharacterInterface* HitCharacter = Cast<IBaseRpgCharacterInterface>(HitResult.GetActor());
			if (HitCharacter) {
				HitCharacters.AddUnique(HitResult.GetActor());
			}
		}
		PotentialTargets = HitCharacters;
		if (PotentialTargets.Num() > 0)
		{
			if (ULockOnComponent::FindClosestActor())
			{
				ULockOnComponent::BeginTargeting();
			}
			else
			{
				ULockOnComponent::StopTargeting();
			}
		}
	}
}

void ULockOnComponent::SwitchTarget(bool ToTheRight)
{
	if (PotentialTargets.IsEmpty()) return;
	if (PotentialTargets.Num() < 2) return;
	if (!TargetedActor) return;
	int TargetsNumber = PotentialTargets.Num();
	TArray<AActor*> DirectionalTargets;
	if (TargetingTries > 2) {
		TargetingTries = 0;
		StopTargeting();
		return;
	}
	TargetingTries++;
	if (!ToTheRight)
	{
		float TargetXDistance = 99999.f;
		for (auto Target : PotentialTargets)
		{
			if (IsValid(Target) && Target != TargetedActor)
			{
				FVector TargetLocation = Target->GetActorLocation();
				FVector OwnerLocation = CharacterOwner->GetActorLocation();
				FVector Direction = TargetLocation - OwnerLocation;
				FVector CurrentTargetDirection = TargetedActor->GetActorLocation() - OwnerLocation;
				if (Direction.Y > CurrentTargetDirection.Y)
				{
					DirectionalTargets.Add(Target);
				}
			}
		}
	}
	else {
		for (auto Target : PotentialTargets)
		{
			if (IsValid(Target) && Target != TargetedActor)
			{
				FVector TargetLocation = Target->GetActorLocation();
				FVector OwnerLocation = CharacterOwner->GetActorLocation();
				FVector Direction = TargetLocation - OwnerLocation;
				FVector CurrentTargetDirection = TargetedActor->GetActorLocation() - OwnerLocation;
				if (Direction.Y < CurrentTargetDirection.Y)
				{
					DirectionalTargets.Add(Target);
				}
			}
		}
	}
	float ClosestDistance = 99999.f;
	if (!DirectionalTargets.IsEmpty())
	{
		for (auto Target : DirectionalTargets)
		{
			if (IsValid(Target))
			{
				FVector TargetLocation = Target->GetActorLocation();
				FVector OwnerLocation = CharacterOwner->GetActorLocation();
				FVector Direction = TargetLocation - OwnerLocation;
				float Distance = Direction.Size();
				if (Distance < ClosestDistance)
				{
					ClosestDistance = Distance;
					TargetedActor = Target;
				}
			}
		}
	}
	else {
		if (DirectionalTargets.Num() > 0 && PotentialTargets.Num() > 0)
		{
			TargetedActor = DirectionalTargets[0];
		}
		SwitchTarget(!ToTheRight);
	}
}

void ULockOnComponent::OnEnemyKilled(AActor* KilledEnemy)
{
	if (IsValid(KilledEnemy))
	{
		PotentialTargets.Remove(KilledEnemy);
		if (KilledEnemy == TargetedActor)
		{
			ULockOnComponent::FindNextTarget();
		}
	}
}

void ULockOnComponent::FindNextTarget()
{
	if (!PotentialTargets.IsEmpty())
	{
		AActor* ClosestActor = nullptr;
		float ClosestDistance = 99999.f;
		for (auto Target : PotentialTargets)
		{
			if (IsValid(Target))
			{
				float Distance = (Target->GetActorLocation() - CharacterOwner->GetActorLocation()).Size();
				if (Distance < ClosestDistance)
				{
					ClosestActor = Target;
					ClosestDistance = Distance;
				}
			}
		}
	}
	else {
		ULockOnComponent::StopTargeting();
	}
}


void ULockOnComponent::StopTargeting()
{
	if (IsTargeting)
	{
		IsTargeting = false;
		//updates the UI
		OnLockedOn.Broadcast(false);
		TargetedActor = nullptr;
		GetWorld()->GetTimerManager().PauseTimer(LockonTimerHandler);
	}
}

void ULockOnComponent::BeginTargeting()
{
	IsTargeting = true;
	OnLockedOn.Broadcast(true);
	GetWorld()->GetTimerManager().SetTimer(LockonTimerHandler, ContinueLockingOn, LockOnInterval, true);
}

void ULockOnComponent::SwitchTargetingCamera(bool ShouldBeEnabled)
{
	//if (ULockOnComponent)
	//{
	//	if (ShouldBeEnabled)
	//	{
	//		CharacterOwner->Rotation
	//	}
	//	else
	//	{
	//		CharacterOwner->bUseControllerRotationYaw = false;
	//	}
	//}
}