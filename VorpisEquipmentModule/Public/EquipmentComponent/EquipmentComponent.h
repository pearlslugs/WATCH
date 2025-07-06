// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAsset/ItemDataAsset.h"
#include "ItemInterfaces/EquipmentComponentInterface.h"
#include "ItemData/ItemEnums.h"
#include "ItemData/ItemStructs.h"
#include "EquipmentComponent.generated.h"



UENUM(BlueprintType)
enum class EStackableRejectionReason : uint8
{
	ESRR_None UMETA(DisplayName = "None"),
	ESRR_NotStackable UMETA(DisplayName = "Not Stackable"),
	ESRR_StackLimitReached UMETA(DisplayName = "Stack Limit Reached"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnError, FString, ErrorString);
// called when items are added or removed from, equip means equip or unequipped
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FAffectEquipmentStaticMeshes, FItemData, NewItem, bool, CreateOrDestroy, bool, EquipSocket, bool, RightHand);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, FItemData, ItemData, int, Slot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VORPISEQUIPMENTMODULE_API UEquipmentComponent : public UActorComponent, public IEquipmentComponentInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

	UPROPERTY(BlueprintAssignable)
	FOnError OnError;
	UPROPERTY(BlueprintAssignable)
	FAffectEquipmentStaticMeshes AffectEquipmentStaticMeshes;
	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemAdded;
	UPROPERTY(BlueprintAssignable)
	FOnInventoryChanged OnInventoryChanged;

	// init
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	UItemDataAsset* BlankAsset;
	UFUNCTION(BlueprintCallable)
	bool IsItemBlank(FItemData ItemToTest) { return ItemToTest.ItemAsset == BlankAsset; }
	UFUNCTION(BlueprintCallable)
	void PickUpItem(FItemData ItemToPickUp, bool RightHand);

	// equipped items
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void EquipItem(FItemData ItemData, EEquipmentSlot Slot);
	UFUNCTION(BlueprintPure, Category = "Equipment")
	FItemData GetEquippedItem(EEquipmentSlot Slot);
	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool GetIsSlotEmpty(EEquipmentSlot Slot);
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	FItemData UnequipItem(EEquipmentSlot Slot);
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	FItemData SwapItem(EEquipmentSlot Slot, FItemData ItemToUse);


	// quickslots
	UFUNCTION(BlueprintCallable)
	void SetDefaultQuickslots();
	UFUNCTION(BlueprintCallable)
	void RecieveSavedQuickslots(TMap<int, FItemData> NewQuickslots);
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void InitializeQuickslots();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int QuickslotsLength = 6;
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void AddItemToQuickslots(FItemData ItemData, int Slot, bool UpdateSave);
	UFUNCTION(BlueprintPure, Category = "Equipment")
	int GetFirstEmptyQuickslot();
	UFUNCTION(BlueprintPure, Category = "Equipment")
	FItemData GetQuickslot(int Slot);
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	FItemData RemoveQuickslot(int Slot);
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	FItemData SwapQuickslot(int slot, FItemData ItemToUse);
	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool GetIsQuickslotEmpty(int Slot);

	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	int LeftOverItemAmount = -1;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	int SelectedQuickslot = 0;
	UPROPERTY(BlueprintReadOnly)
	int HoveredQuickslot = 0;
	UFUNCTION(BlueprintCallable)
	void SetHoveredQuickslot(int NewIndex) { HoveredQuickslot = NewIndex; }
	UFUNCTION(BlueprintCallable)
	void SetSelectedQuickslot(int NewIndex) { SelectedQuickslot = NewIndex; }
	UFUNCTION(BlueprintCallable)
	void IncrementSelectedQuickslot();
	UFUNCTION(BlueprintCallable)
	void DecrementSelectedQuickslot();
	UFUNCTION(BlueprintCallable)
	FGuid GetSelectedQuickslotGuid() { return Quickslots[SelectedQuickslot].ItemGuid; }


	// stackable items
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	EStackableRejectionReason AddStackableItemToQuickslot(int ItemAmount, int Slot);
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	int FindStackableItemInQuickslot(FItemData ItemData);

	UFUNCTION(BlueprintCallable)
	void RecieveQuickslots(TMap<int, FItemData> QuickslotsToRecieve);

	UFUNCTION(BlueprintPure)
	FItemData GetRightHandItem() { return EquippedRightHandItem; }
	UFUNCTION(BlueprintPure)
	FItemData GetLeftHandItem() { return EquippedLeftHandItem; }
	UFUNCTION(BlueprintCallable)
	void SetRightHandItem(FItemData NewItem, bool UpdateSave);
	UFUNCTION(BlueprintCallable)
	void SetLeftHandItem(FItemData NewItem, bool UpdateSave);

	// when the player adds a tool to their equip slots, the tool  properties need to be added to this so taht they can do tasks
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<EToolProperties, int> CurrentToolProperties;
	UFUNCTION()
	void AddToolProperties(EToolProperties Property, int Value);
	UFUNCTION(BlueprintCallable)
	FToolCompareType CompareToolCapabilities(TMap<EToolProperties, int> RequiredTools);

	UFUNCTION(BlueprintCallable)
	TArray<FItemData> GetQuickslotsArray();
	UFUNCTION(BlueprintCallable)
	FItemData FindItemByGuid(FGuid ItemGuid);

	// item data
	UFUNCTION(BlueprintCallable)
	void UpdateLeftHandItemTaskMap(ETaskType Task, bool Condition);
	UFUNCTION(BlueprintCallable)
	void SyncLeftHandedItemData();
	UFUNCTION(BlueprintCallable)
	void SyncRightHandedItemData();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// DEPRICATED, REPLACE WITH EQUIPMENT SLOT
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FItemData EquippedRightHandItem;
	// DEPRICATED, REPLACE WITH EQUIPMENT SLOT
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FItemData EquippedLeftHandItem;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<EEquipmentSlot, FItemData> EquippedItems;
	UFUNCTION(BlueprintCallable)
	FItemData GetEquippedSlot(EEquipmentSlot Slot);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<int, FItemData> Quickslots;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	virtual void InterfaceEquipItem(FItemData ItemData, EEquipmentSlot Slot) override;
	virtual FItemData InterfaceGetEquippedItem(EEquipmentSlot Slot) override;
	virtual bool InterfaceGetIsSlotEmpty(EEquipmentSlot Slot) override;
	virtual FItemData InterfaceUnequipItem(EEquipmentSlot Slot) override;
	virtual FItemData InterfaceSwapItem(EEquipmentSlot Slot, FItemData ItemToUse) override;

	virtual void InterfaceAddItemToQuickslots(FItemData ItemData, int Slot) override;
	virtual int InterfaceGetFirstEmptyQuickslot() override;
	virtual FItemData InterfaceGetQuickslot(int Slot) override;
	virtual FItemData InterfaceRemoveQuickslot(int Slot) override;
	virtual FItemData InterfaceSwapQuickslot(int slot, FItemData ItemToUse) override;
	virtual bool InterfaceGetIsQuickslotEmpty(int Slot) override;
		
};
