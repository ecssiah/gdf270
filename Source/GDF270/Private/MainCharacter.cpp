#include "MainCharacter.h"

#include "PlayerData.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"


AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	DebugLineTrace = true;
	
	GetCharacterMovement()->AirControl = 1.0f;
	
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	
	VoxelWorld = Cast<AVoxelWorld>(
		UGameplayStatics::GetActorOfClass(this, AVoxelWorld::StaticClass())
	);
}

void 
AMainCharacter::AddBlock()
{
	const EBlockKind SelectedBlockKind = InventoryComponent->GetSelectedBlockKind();
	
	if (SelectedBlockKind == EBlockKind::None)
	{
		return;
	}
	
	const FHitResult Hit = RunLineTrace();

	if (Hit.bBlockingHit)
	{
		const bool AddResult = VoxelWorld->TryAddBlockFromHit(Hit, SelectedBlockKind);
		
		if (AddResult)
		{
			InventoryComponent->TryRemoveBlock(SelectedBlockKind);
		}
	}
}

void 
AMainCharacter::RemoveBlock()
{
	const FHitResult Hit = RunLineTrace();
	
	if (Hit.bBlockingHit)
	{
		const EBlockKind RemovedBlockKind = VoxelWorld->TryRemoveBlockFromHit(Hit);
		
		if (RemovedBlockKind != EBlockKind::None)
		{
			InventoryComponent->TryAddBlock(RemovedBlockKind);
		}
	}
}

FHitResult 
AMainCharacter::RunLineTrace()
{
	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	
	FVector StartLocation;
	FRotator Rotation;
	
	PlayerController->GetPlayerViewPoint(StartLocation, Rotation);
	
	const FVector EndLocation = StartLocation + Rotation.Vector() * PlayerReachDistance * CellSizeInCentimeters;
	
	FHitResult Hit;
	
	GetWorld()->LineTraceSingleByChannel(
		Hit,
		StartLocation,
		EndLocation,
		ECC_Visibility
	);
	
	if (DebugLineTrace)
	{
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			EndLocation,
			FColor::Red,
			false,
			5.0f,
			0,
			1.0f
		);
	}

	if (Hit.bBlockingHit)
	{
		if (DebugLineTrace)
		{
			DrawDebugPoint(
				GetWorld(),
				Hit.ImpactPoint,
				50.0f,
				FColor::Green,
				false,
				5.0f
			);
		}
	}
	
	return Hit;
}
