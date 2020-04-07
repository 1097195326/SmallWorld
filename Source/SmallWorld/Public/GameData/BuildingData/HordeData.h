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
	~HordeData();

    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	BaseBuildingData *	SpawnBuilding(const FString & BuildingName);
	bool	DestroyBuildingById(const FGuid & InId);
	bool	DestroyBuilding(BaseBuildingData * InBuildingData);
	template<typename BuildingClass = BaseBuildingData>
	TArray<BuildingClass *> GetBuildingDatasByType(EBuildingType BuildingType)
	{
		TArray<BuildingClass *> TemArray;
		if (BuildingDatas.Num() > 0)
		{
			for (auto building : BuildingDatas)
			{
				if (building.Value->GetBuildingType() == BuildingType)
				{
					TemArray.Add((BuildingClass*)(building.Value));
				}
			}
		}
		return MoveTemp(TemArray);
	}
	BaseBuildingData * GetBuildingDataById(const FGuid & InId);


	int32 GetGoldNum();
	int32 GetWoodNum();
	int32 GetStoneNum();

	
protected:
	TMap<FGuid, BaseBuildingData*>		BuildingDatas;
	//TArray<BaseBuildingData*>		BuildingDatas;

};

