#pragma once

#include "CoreMinimal.h"
#include "WorldData.h"
#include "SectorComponent.h"
#include "GameFramework/Actor.h"
#include "VoxelWorld.generated.h"

UCLASS()
class AVoxelWorld : public AActor
{
	
	GENERATED_BODY()
	
public:	

	AVoxelWorld();
	
	UPROPERTY()
	APawn* PlayerPawn;
	
	UPROPERTY(EditAnywhere)
	UMaterialInterface* BlockMaterial;
	
	UFUNCTION(BlueprintPure, Category="Voxel")
	FIntVector GetPlayerCellCoordinate() const;
	
	UFUNCTION(BlueprintPure, Category="Voxel")
	FIntVector2 GetPlayerSectorCoordinate() const;
	
	UFUNCTION(BlueprintCallable, Category="Voxel")
	void AddBlock();
	
	UFUNCTION(BlueprintCallable, Category="Voxel")
	void RemoveBlock();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	
	float PlayerLocationOffset;
	
	FIntVector PlayerCellCoordinate;
	FIntVector2 PlayerSectorCoordinate;
	
	TArray<FCell> CellArray;
	TArray<FSectorMesh> SectorMeshArray;
	
	TArray<TObjectPtr<USectorComponent>> FreeSectorComponentArray;
	TMap<FIntVector2, TObjectPtr<USectorComponent>> SectorComponentMap;
	
	static bool CellCoordinateIsValid(const FIntVector& CellCoordinate);
	static FIntVector CellIndexToCellCoordinate(int32 CellIndex);
	static int32 CellCoordinateToCellIndex(const FIntVector& CellCoordinate);
	
	static bool SectorCoordinateIsValid(const FIntVector2& SectorCoordinate);
	static FIntVector2 SectorIndexToSectorCoordinate(int32 SectorIndex);
	static int32 SectorCoordinateToSectorIndex(const FIntVector2& SectorCoordinate);
	static FIntVector SectorCoordinateToCellCoordinate(const FIntVector2& SectorCoordinate);
	
	static FIntVector WorldLocationToCellCoordinate(const FVector& WorldLocation);
	static FIntVector2 WorldLocationToSectorCoordinate(const FVector& WorldLocation);
	
	FCell& GetCell(const FIntVector& CellCoordinate);
	
	void GenerateWorld();
	
	void BuildSectorMeshes();
	FSectorMesh BuildSectorMesh(int32 SectorIndex);
	
	void InitPlayer();
	void InitSectorCache();
	
	void UpdateSectorComponents();
	
	void AddSectorComponent(const FIntVector2& SectorCoordinate);
	void RemoveSectorComponent(const FIntVector2& SectorCoordinate);
	
	uint8 CalculateNeighborSet(const FCell& Cell);
	
};
