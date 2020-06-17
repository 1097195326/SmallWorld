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
#include "WoodStoneStoreActor.h"
#include "TreeActor.h"
#include "WoodStoreActor.h"
#include "BlockActor.h"
#include "GateActor.h"
#include "TowerActor.h"
#include "WallActor.h"
#include "HordeData.h"

//#include "TGeneralGoal.h"
#include "SoldierGroupManager.h"

#include "CityActor.generated.h"

UCLASS()
class SMALLWORLD_API ACityActor : public ABaseBuildingActor
{
	GENERATED_BODY()

public:
	ACityActor();

	virtual void On_Init() override;
	virtual void On_Delete() override;
	virtual void On_GameUpdate() override;
    
	virtual TSharedPtr<SWidget>	CreateActorDetailWidget() override;

private:
	
	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent * CollisionBox;

	//GeneralGoal *					mGeneralGoal;

	list<SoldierGroupManager*>		mGroupManagers;

private:
	
};
