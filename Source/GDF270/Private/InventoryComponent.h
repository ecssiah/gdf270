#pragma once

#include "CoreMinimal.h"
#include "PlayerData.h"
#include "WorldData.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup=(Voxel), meta=(BlueprintSpawnableComponent))
class GDF270_API UInventoryComponent : public UActorComponent
{
	
	GENERATED_BODY()

public:
	
	UInventoryComponent();
	
	UFUNCTION(BlueprintCallable)
	void SelectSlot(int32 SlotIndex);
	
	UFUNCTION(BlueprintCallable)
	EBlockKind GetSelectedBlockKind() const;
	
	UFUNCTION(BlueprintCallable)
	bool HasBlock(EBlockKind BlockKind, int32 Count = 1) const;
	
	UFUNCTION(BlueprintCallable)
	bool TryAddBlock(EBlockKind BlockKind, int32 Count = 1);
	
	UFUNCTION(BlueprintCallable)
	bool TryRemoveBlock(EBlockKind BlockKind, int32 Count = 1);

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
