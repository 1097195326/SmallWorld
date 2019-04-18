#pragma once

#include "BaseBuildingActor.h"
#include "BlockData.h"
#include "BlockActor.generated.h"

class ACityActor;



UCLASS()
class ABlockActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	ABlockActor();
	virtual void On_Init() override;

	void InitData(BlockData * Data);

	void SetCity(ACityActor * _City);
	ACityActor * GetCity();

	void SetMesh();

	virtual bool IsInWorld() override;

private:
	BlockData * mData;
	ACityActor * mCity;

	FString GrassCentreDirtTile;
	FString GrassFullDirtTiles;
	FString GrassTile;
	FString GrassToDirtEdgeTile;
	FString GrassToDirtTile;
	FString DirtTile;
};