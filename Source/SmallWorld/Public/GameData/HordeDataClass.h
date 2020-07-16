#pragma once

#include "BaseBuildingDataClass.h"
#include "ArmyCenterDataClass.h"
#include "BakeryDataClass.h"
#include "CommandCenterDataClass.h"
#include "FarmDataClass.h"
#include "FoodStoreDataClass.h"
#include "FruitFarmDataClass.h"
#include "GateDataClass.h"
#include "HouseDataClass.h"
#include "MillDataClass.h"
#include "MoneyStoreDataClass.h"
#include "WoodStoneStoreDataClass.h"
#include "TowerDataClass.h"
#include "WallDataClass.h"


class HordeDataClass : public RuntimeDataClass
{
public:
	HordeDataClass(RaceEnum InRace);
	~HordeDataClass();

    virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
    virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	BaseBuildingDataClass *	SpawnBuildingData(const FString & BuildingName);
	bool	DestroyBuildingById(const FGuid & InId);
	bool	DestroyBuilding(BaseBuildingDataClass * InBuildingData);
	template<typename BuildingClass = BaseBuildingDataClass>
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
	BaseBuildingDataClass * GetBuildingDataById(const FGuid & InId);


	int32 GetGoldNum();
	int32 GetWoodNum();
	int32 GetStoneNum();
	inline RaceEnum GetRace() { return Race; }
	
protected:
	TMap<FGuid, BaseBuildingDataClass*>		BuildingDatas;
	//TArray<BaseBuildingDataClass*>		BuildingDatas;
	RaceEnum		Race;
	
};

