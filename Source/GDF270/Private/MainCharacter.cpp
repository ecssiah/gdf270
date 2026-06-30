#include "MainCharacter.h"


AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	InventoryComponent->Init();
}

void 
AMainCharacter::AddBlock()
{
	UE_LOG(LogTemp, Warning, TEXT("AddBlock"));
}
	
void 
AMainCharacter::RemoveBlock()
{
	UE_LOG(LogTemp, Warning, TEXT("RemoveBlock"));
}

