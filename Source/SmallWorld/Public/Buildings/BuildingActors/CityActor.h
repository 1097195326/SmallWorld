#pragma once

#include "BaseBuildingActor.h"
#include "ArmyCenterActor.h"
#include "BakeryActor.h"
#include "CommandCenterActor.h"
#include "FarmActor.h"
#include "FoodStoreActor.h"
#include "HouseActor.h"
#include "MillActor.h"
#include "MineActor.h"
#include "MoneyStoreActor.h"
#include "StoneActor.h"
#include "StoneStoreActor.h"
#include "TreeActor.h"
#include "TreeStoreActor.h"
#include "BlockActor.h"
#include "GateActor.h"
#include "TowerActor.h"
#include "WallActor.h"
#include "CityData.h"
#include "CityActor.generated.h"

UCLASS()
class ACityActor : public ABaseBuildingActor
{
	GENERATED_BODY()

private:
	vector<vector<ABlockActor*>> BlockMap;

	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent * CollisionBox;

    
    list<AArmyCenterActor *>        ArmyCenterList;
    list<ABakeryActor *>            BakeryList;
    list<ACommandCenterActor *>     CommandCenterList;
    list<AFarmActor *>              FarmList;
    list<AHouseActor *>             HouseList;
    list<AMillActor *>              MillList;
    list<AMoneyStoreActor *>        MoneyStoreList;
    list<AFoodStoreActor *>         FoodStoreList;
    list<AStoneStoreActor *>        StoneStoreList;
    list<ATreeStoreActor *>         TreeStoreList;
    list<AWallActor *>              WallList;
    list<ATowerActor *>             TowerList;
    list<AGateActor *>              GateList;
    
	bool  mCityIsFull;
	bool  mCenterCityIsFull;

public:
	ACityActor();

	virtual void On_Init() override;
	virtual void On_Delete() override;

	virtual void InitData(BaseBuildingData * _data) override;
    
	bool	CityIsFull();
	bool	CenterCityIsFull();

	int		GetFarmNum();
	int		GetHouseNum();
	int		GetMillNum();
	int		GetBakeryNum();
	int		GetMoneyStoreNum();
	int		GetFoodStoreNum();
	int		GetStoneStoreNum();
	int		GetTreeStoreNum();

	int		GetCommandCenterLevel();
	int		GetArmyCenterLevel();
	int		GetWallLevel();
	int		GetMillLevel();
	int		GetBakeryLevel();
	int		GetMoneyStoreLevel();
	int		GetFoodStoreLevel();
	int		GetStoneStoreLevel();
	int		GetTreeStoreLevel();

	bool CheckCanBuildCommandCenter(ABlockActor * OutBlockActor,FString & OutMsg);
	bool CheckCanBuildArmyCenter(ABlockActor * OutBlockActor,FString & OutMsg);
	bool CheckCanBuildBakery(ABlockActor * OutBlockActor, FString & OutMsg);
	bool CheckCanBuildFarm(ABlockActor * OutBlockActor, FString & OutMsg);
	bool CheckCanBuildHouse(ABlockActor * OutBlockActor, FString & OutMsg);
	bool CheckCanBuildMill(ABlockActor * OutBlockActor, FString & OutMsg);
	bool CheckCanBuildMoneyStore(ABlockActor * OutBlockActor, FString & OutMsg);
	bool CheckCanBuildFoodStore(ABlockActor * OutBlockActor, FString & OutMsg);
	bool CheckCanBuildStoneStore(ABlockActor * OutBlockActor, FString & OutMsg);
	bool CheckCanBuildTreeStore(ABlockActor * OutBlockActor, FString & OutMsg);
	bool CheckCanBuildWall(ABlockActor * OutBlockActor, FString & OutMsg);

	bool BuildCommandCenter();
	bool BuildArmyCenter();
	bool BuildBakery();
	bool BuildFarm();
	bool BuildHouse();
	bool BuildMill();
	bool BuildMoneyStore();
	bool BuildFoodStore();
	bool BuildStoneStore();
	bool BuildTreeStore();
	bool BuildWall();
    
    
private:
	
    
    void CalCulateOrientation(int _x,int _y, ABlockActor * _blockActor);
    
    
	vector<ABlockActor*>	ControllBuildTiles;    // Controll Can Build Tiles
	//vector<ABlockActor*>	OutControllBuildTiles; //  Out Controll Can Build Tiles
    
	vector<ABlockActor*>	CornerOutControllLeftBottom;
	vector<ABlockActor*>	CornerOutControllLeftTop;
	vector<ABlockActor*> 	CornerOutControllRightBottom;
	vector<ABlockActor*> 	CornerOutControllRightTop;

	vector<ABlockActor*> 	CenterOutControllLeft;
	vector<ABlockActor*> 	CenterOutControllRight;
	vector<ABlockActor*> 	CenterOutControllTop;
	vector<ABlockActor*> 	CenterOutControllBottom;

	vector<ABlockActor*>	OutSkirtOutControllLeftBottom;
	vector<ABlockActor*>	OutSkirtOutControllLeftTop;
	vector<ABlockActor*> 	OutSkirtOutControllRightBottom;
	vector<ABlockActor*> 	OutSkirtOutControllRightTop;
	vector<ABlockActor*> 	OutSkirtOutControllTopLeft;
	vector<ABlockActor*> 	OutSkirtOutControllTopRight;
	vector<ABlockActor*> 	OutSkirtOutControllBottomLeft;
	vector<ABlockActor*> 	OutSkirtOutControllBottomRight;

	vector<ABlockActor*> 	FarmOutControllLeftBottom;
	vector<ABlockActor*> 	FarmOutControllLeftTop;
	vector<ABlockActor*> 	FarmOutControllRightBottom;
	vector<ABlockActor*> 	FarmOutControllRightTop;
	vector<ABlockActor*> 	FarmOutControllTopLeft;
	vector<ABlockActor*> 	FarmOutControllTopRight;
	vector<ABlockActor*> 	FarmOutControllBottomLeft;
	vector<ABlockActor*>	FarmOutControllBottomRight;
	// Controll
	vector<ABlockActor*> 	CornerControllLeftBottom;
	vector<ABlockActor*> 	CornerControllLeftTop;
	vector<ABlockActor*> 	CornerControllRightBottom;
	vector<ABlockActor*> 	CornerControllRightTop;
	vector<ABlockActor*> 	CenterControllLeft;
	vector<ABlockActor*> 	CenterControllRight;
	vector<ABlockActor*> 	CenterControllTop;
	vector<ABlockActor*> 	CenterControllBottom;
	vector<ABlockActor*> 	FarmControllLeftBottom;
	vector<ABlockActor*> 	FarmControllLeftTop;
	vector<ABlockActor*> 	FarmControllRightBottom;
	vector<ABlockActor*> 	FarmControllRightTop;
	vector<ABlockActor*> 	FarmControllTopLeft;
	vector<ABlockActor*> 	FarmControllTopRight;
	vector<ABlockActor*> 	FarmControllBottomLeft;
	vector<ABlockActor*> 	FarmControllBottomRight;
	// In Castle
	vector<ABlockActor*> 	CornerCastleLeftBottom;
	vector<ABlockActor*> 	CornerCastleLeftTop;
	vector<ABlockActor*> 	CornerCastleRightBottom;
	vector<ABlockActor*> 	CornerCastleRightTop;

	vector<ABlockActor*> 	CenterCastleLeft;
	vector<ABlockActor*>	CenterCastleRight;
	vector<ABlockActor*> 	CenterCastleTop;
	vector<ABlockActor*> 	CenterCastleBottom;
	// City Center
	vector<ABlockActor*> 	CenterCity;
	ABlockActor* 			CenterOfCenterCity;
};
