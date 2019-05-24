#pragma once
#include "DataR.h"
#include "CoreMinimal.h"
#include "GameConfig.h"


#define  ZHX_BUG

struct BuildingIndex
{
    int X;
    int Y;
    BuildingIndex():X(-1),Y(-1) {}
    BuildingIndex(int _x, int _y) :X(_x), Y(_y)
    {
        
    }
};
enum BlockTitleType
{
    T_GrassTile,
    T_DirtTile,
    T_CenterDirtTile,
    T_EdgeDirtTile,
    T_CornerDirtTile,
    T_FullDirtTile,
};
enum BuildingType
{
	B_None,

	B_World,

	B_City,
	B_CityBlock,

	B_Tree,
	B_Stone,
	B_Mine,
	B_Farm,
	B_House,
	B_Wall,
	B_Tower,
	B_Gate,
	B_CommandCenter,
	B_ArmyCenter,
	B_FoodStore,
	B_WoodStore,
	B_StoneStore,
	B_MoneyStore,

	B_Bakery,
	B_Mill,

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
    Center_City,
    CenterOfCenter_City,
    
    
};
enum BuildingDirection
{
    Dir_None,
    
    Dir_Corner_City_LeftBottom,
    Dir_Corner_City_LeftTop,
    Dir_Corner_City_RightBottom,
    Dir_Corner_City_RightTop,
    
    Dir_CityEdge_Left,
    Dir_CityEdge_Right,
    Dir_CityEdge_Top,
    Dir_CityEdge_Bottom,
    
    Dir_Corner_Castle_LeftBottom,
    Dir_Corner_Castle_LeftTop,
    Dir_Corner_Castle_RightBottom,
    Dir_Corner_Castle_RightTop,
    
    Dir_CastleEdge_Left,
    Dir_CastleEdge_Right,
    Dir_CastleEdge_Top,
    Dir_CastleEdge_Bottom,
    
    
};


class BaseBuildingData : public DataR
{

public:
    
    FVector     mPosition;
    FRotator    mRotator;
    
	float	    mHealth;
	int		    mLevel;
    
    BuildingIndex           mIndex;
    BuildingType            mType;
    CityOrientation         mCityOrientation;
    BuildingDirection       mDirection;
    BlockTitleType          mBlockTileType;

public:
    BaseBuildingData();
    
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

    
};
