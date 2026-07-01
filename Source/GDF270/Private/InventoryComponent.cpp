#include "InventoryComponent.h"

#include "PlayerData.h"

UInventoryComponent::UInventoryComponent()
{
	for (int32 StackIndex = 0; StackIndex < MaxSlots; StackIndex++)
	{
		FBlockStack BlockStack;
		
		if (StackIndex == 0)
		{
			BlockStack.BlockKind = EBlockKind::PurpleStone;
			BlockStack.Count = 32;
		}

		SlotArray.Add(BlockStack);
	}
}

void 
UInventoryComponent::SelectSlot(int32 SlotIndex)
{
	SelectedSlotIndex = SlotIndex;
}
	
EBlockKind 
UInventoryComponent::GetSelectedBlockKind() const
{
	return SlotArray[SelectedSlotIndex].BlockKind;
}

bool 
UInventoryComponent::HasBlock(EBlockKind BlockKind, int32 Count) const
{
	const FBlockStack* BlockStackPtr = SlotArray.FindByPredicate(
		[BlockKind, Count](const FBlockStack& Stack)
		{
			return Stack.BlockKind == BlockKind && Stack.Count >= Count;
		}
	);
	
	return BlockStackPtr != nullptr;
}
	
bool 
UInventoryComponent::TryAddBlock(EBlockKind BlockKind, int32 Count)
{
	for (int32 StackIndex = 0; StackIndex < SlotArray.Num(); StackIndex++)
	{
		FBlockStack& Stack = SlotArray[StackIndex];
		
		if (Stack.BlockKind == BlockKind)
		{
			const int32 Capacity = MaxStackSize - Stack.Count;
			
			if (Capacity >= Count)
			{
				Stack.Count += Count;
				
				return true;
			}
		}
	}
	
	for (int32 StackIndex = 0; StackIndex < SlotArray.Num(); StackIndex++)
	{
		FBlockStack& Stack = SlotArray[StackIndex];
		
		if (Stack.BlockKind == EBlockKind::None)
		{
			Stack.BlockKind = BlockKind;
			Stack.Count = Count;
			
			return true;
		}
	}
	
	return false;
}
	
bool 
UInventoryComponent::TryRemoveBlock(EBlockKind BlockKind, int32 Count)
{
	for (int32 StackIndex = 0; StackIndex < SlotArray.Num(); StackIndex++)
	{
		FBlockStack& Stack = SlotArray[StackIndex];
		
		if (Stack.BlockKind == BlockKind)
		{
			if (Stack.Count >= Count)
			{
				Stack.Count -= Count;
				
				return true;
			}
		}
	}
	
	return false;
}
