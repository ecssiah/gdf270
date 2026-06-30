// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldData.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup=(Voxel), meta=(BlueprintSpawnableComponent))
class GDF270_API UInventoryComponent : public UActorComponent
{
	
	GENERATED_BODY()

public:
	
	void Init();

	UFUNCTION(BlueprintCallable)
	bool HasBlock(EBlockKind BlockKind, int32 Count = 1) const;
	
	UFUNCTION(BlueprintCallable)
	bool TryAddBlock(EBlockKind BlockKind, int32 Count = 1);
	
	UFUNCTION(BlueprintCallable)
	bool TryRemoveBlock(EBlockKind BlockKind, int32 Count = 1);
	
	UFUNCTION(BlueprintCallable)
	EBlockKind GetSelectedBlockKind() const;
	
	UFUNCTION(BlueprintCallable)
	void SelectSlot(int32 SlotIndex);

private:

	UPROPERTY(EditAnywhere)
	int32 MaxSlots = 8;
	
	UPROPERTY(EditAnywhere)
	int32 MaxStackSize = 64;
	
	UPROPERTY(VisibleAnywhere)
	int32 SelectedSlotIndex = 0;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FBlockStack> SlotArray;

};
