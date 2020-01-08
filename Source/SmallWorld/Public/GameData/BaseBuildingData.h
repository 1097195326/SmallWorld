#pragma once
#include "DataR.h"
#include "CoreMinimal.h"
#include "GameConfig.h"


#define  ZHX_BUG

enum EBuildingType
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


class BaseBuildingData : public DataR
{

public:
	friend class ABaseBuildingActor;

    BaseBuildingData();
    
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	
	public:
	FVector     BuildingPosition;
	FRotator    BuildingRotator;
	float	    BuildingHealth;
	int32		    BuildingLevel;
	EBuildingType	BuildingType;

};
