#pragma once

#include "BaseBuildingActor.h"
#include "BlockData.h"
#include "BlockActor.generated.h"

UCLASS()
class ABlockActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	ABlockActor();
	void InitData(BlockData * Data);
	void SetMesh();

private:
	BlockData * mData;

	FString GrassCentreDirtTile;
	FString GrassFullDirtTiles;
	FString GrassTile;
	FString GrassToDirtEdgeTile;
	FString GrassToDirtTile;
	FString DirtTile;
};