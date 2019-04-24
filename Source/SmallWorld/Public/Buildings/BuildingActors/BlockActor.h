#pragma once

#include "BaseBuildingActor.h"
#include "BlockData.h"
#include "BlockActor.generated.h"

class ACityActor;

enum BlockTitleType
{
	T_GrassTile,
	T_DirtTile, 
	T_CenterDirtTile,
	T_EdgeDirtTile,
	T_CornerDirtTile,
	T_FullDirtTile,
};


UCLASS()
class ABlockActor : public ABaseBuildingActor
{
	GENERATED_BODY()

private:
	BlockTitleType mTitleType;
	CityOrientation mCityOrientation;

	BlockData * mData;
	ACityActor * mCity;

	FString GrassCentreDirtTile;
	FString GrassFullDirtTiles;
	FString GrassTile;
	FString GrassToDirtEdgeTile;
	FString GrassToDirtTile;
	FString DirtTile;
public:
	ABlockActor();
	virtual void On_Init() override;

	void InitData(BlockData * Data);

	void SetTileType(BlockTitleType _type);
	BlockTitleType GetTileType();
	void SetOrientation(CityOrientation _orientation);
	CityOrientation GetOrientation();

	void SetCity(ACityActor * _City);
	ACityActor * GetCity();

	void SetMesh();

	virtual bool IsInWorld() override;

private:
	virtual FString GetMeshPath() override;
};