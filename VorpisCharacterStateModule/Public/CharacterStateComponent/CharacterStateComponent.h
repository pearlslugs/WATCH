// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStateData/CharacterStateEnums.h"
#include "CharacterStateComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VORPISCHARACTERSTATEMODULE_API UCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterStateComponent();

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetCharacterGeneralState(EGeneralState NewState) { CurrentCharacterState = NewState; };
	UFUNCTION(BlueprintPure, Category = "Character State")
	EGeneralState GetCharacterGeneralState() { return CurrentCharacterState; };

	UFUNCTION(BlueprintCallable, Category = "Combat State")
	void SetCharacterCombatState(ECombatState NewState) { CurrentCombatState = NewState; };
	UFUNCTION(BlueprintPure, Category = "Combat State")
	ECombatState GetCharacterCombatState() { return CurrentCombatState; };

	UFUNCTION(BlueprintCallable, Category = "Personality")
	void SetCharacterPersonality(ECharacterPersonality NewPersonality) { CurrentPersonality = NewPersonality; };
	UFUNCTION(BlueprintPure, Category = "Personality")
	ECharacterPersonality GetCharacterPersonality() { return CurrentPersonality; };


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character State")
	EGeneralState CurrentCharacterState = EGeneralState::EGS_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character State")
	ECombatState CurrentCombatState = ECombatState::ECS_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character State")
	ECharacterPersonality CurrentPersonality = ECharacterPersonality::ECP_None;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
