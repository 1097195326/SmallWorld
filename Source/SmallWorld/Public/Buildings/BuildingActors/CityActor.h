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
    
    
public:
	ACityActor();

	virtual void On_Init() override;
	virtual void On_Delete() override;

	virtual void InitData(BaseBuildingData * _data) override;
    
    void BuildArmyCenter();
    void BuildBakery();
    void BuildCommandCenter();
    void BuildFarm();
    void BuildFoodStore();
    void BuildWall();
    void BuildHouse();
    void BuildMill();
    void BuildMoneyStore();
    void BuildStoneStore();
    void BuildTreeStore();
    
    
private:
	
    
    void CalCulateOrientation(int _x,int _y, ABlockActor * _blockActor);
    
    
    
    
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
