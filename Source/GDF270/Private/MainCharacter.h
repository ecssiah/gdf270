#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "VoxelWorld.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class GDF270_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AMainCharacter();
	
	UFUNCTION(BlueprintCallable)
	void AddBlock();
	
	UFUNCTION(BlueprintCallable)
	void RemoveBlock();

private:
	
	bool DebugLineTrace;
	
	UPROPERTY()
	TObjectPtr<AVoxelWorld> VoxelWorld;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInventoryComponent> InventoryComponent;
	
	FHitResult RunLineTrace();
	
};
