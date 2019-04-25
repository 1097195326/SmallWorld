#pragma once
#include "DataR.h"

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
	B_TreeStore,
	B_StoneStore,
	B_MoneyStore,

	B_Bakery,
	B_Mill,

};


class BaseBuildingData : public DataR
{

protected:
	float	Health;
	int		Level;
    BuildingType mType;

public:
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;


};
