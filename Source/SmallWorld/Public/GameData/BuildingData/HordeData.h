#pragma once

#include "BaseBuildingData.h"
#include "ArmyCenterData.h"
#include "BakeryData.h"
#include "CommandCenterData.h"
#include "FarmData.h"
#include "FoodStoreData.h"
#include "FruitFarmData.h"
#include "GateData.h"
#include "HouseData.h"
#include "MillData.h"
#include "MoneyStoreData.h"
#include "WoodStoneStoreData.h"
#include "TowerData.h"
#include "WallData.h"


class HordeData : public DataR
{
public:
    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

    
	int32 GetGoldNum();
	int32 GetWoodNum();
	int32 GetStoneNum();

	template<typename BuildingClass = BaseBuildingData>
	TArray<BuildingClass *> GetBuildingDatas(EBuildingType BuildingType)
	{
		TArray<BuildingClass *> TemArray;
		if (BuildingDatas.Num() > 0)
		{
			for (auto building : BuildingDatas)
			{
				if (building->BuildingType == BuildingType)
				{
					TemArray.Add((BuildingClass*)(building));
				}
			}
		}
		return MoveTemp(TemArray);
	}
protected:
	TArray<BaseBuildingData*>		BuildingDatas;

};

