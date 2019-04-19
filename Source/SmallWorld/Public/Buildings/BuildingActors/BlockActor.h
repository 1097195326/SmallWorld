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

enum CityOrientation
{
	O_None,
	// OutControll 
	CornerOutControll_LeftBottom,
	CornerOutControll_LeftTop,
	CornerOutControll_RightBottom,
	CornerOutControll_RightTop,

	CenterOutControll_Left,
	CenterOutControll_Right,
	CenterOutControll_Top,
	CenterOutControll_Bottom,

	OutSkirtOutControll_LeftBottom,
	OutSkirtOutControll_LeftTop,
	OutSkirtOutControll_RightBottom,
	OutSkirtOutControll_RightTop,
	OutSkirtOutControll_TopLeft,
	OutSkirtOutControll_TopRight,
	OutSkirtOutControll_BottomLeft,
	OutSkirtOutControll_BottomRight,

	FarmOutControll_LeftBottom,
	FarmOutControll_LeftTop,
	FarmOutControll_RightBottom,
	FarmOutControll_RightTop,
	FarmOutControll_TopLeft,
	FarmOutControll_TopRight,
	FarmOutControll_BottomLeft,
	FarmOutControll_BottomRight,
	// Controll
	CornerControll_LeftBottom,
	CornerControll_LeftTop,
	CornerControll_RightBottom,
	CornerControll_RightTop,

	CenterControll_Left,
	CenterControll_Right,
	CenterControll_Top,
	CenterControll_Bottom,

	FarmControll_LeftBottom,
	FarmControll_LeftTop,
	FarmControll_RightBottom,
	FarmControll_RightTop,
	FarmControll_TopLeft,
	FarmControll_TopRight,
	FarmControll_BottomLeft,
	FarmControll_BottomRight,
	// In Castle
	CornerCastle_LeftBottom,
	CornerCastle_LeftTop,
	CornerCastle_RightBottom,
	CornerCastle_RightTop,

	CenterCastle_Left,
	CenterCastle_Right,
	CenterCastle_Top,
	CenterCastle_Bottom,
	// City Center
	CityCenter,
	CenterOfCenter,


};
enum FillType
{
	F_None,
	Tree,
	Stone,
	Money,
	Farm,
	House,
	Wall,
	CommandCenter,
	ArmyCenter,
	FoodStore,
	TreeStore,
	StoneStore,
	MoneyStore,

	Bakery,
	Mill,

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
	FString GetTileString();
};