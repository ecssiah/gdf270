#pragma once

#include "WorldData.h"
#include "PlayerData.generated.h"

constexpr int32 PlayerSectorViewRange = 2;

constexpr float PlayerReachDistance = 4.0f;

USTRUCT(BlueprintType)
struct FBlockStack
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBlockKind BlockKind = EBlockKind::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count = 0;
};