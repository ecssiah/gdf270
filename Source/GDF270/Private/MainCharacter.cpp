#include "MainCharacter.h"


AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

void 
AMainCharacter::AddBlock()
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

	if (Hit.bBlockingHit)
	{
		DrawDebugPoint(
			GetWorld(),
			Hit.ImpactPoint,
			50.0f,
			FColor::Green,
			false,
			5.0f
		);
		
		const FVector RemoveLocation = Hit.ImpactPoint - Hit.ImpactNormal * 0.5f;

		// FIntVector CellCoordinate = WorldLocationToCellCoordinate(RemoveLocation);
	}
}
	
void 
AMainCharacter::RemoveBlock()
{

}
