#include "HordeDataClass.h"
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


HordeDataClass::HordeDataClass(RaceEnum InRace) :Race(InRace)
{

}
HordeDataClass::~HordeDataClass()
{
	for (auto data : BuildingDatas)
	{
		delete data.Value;
	}
	BuildingDatas.Empty();
}
void HordeDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("HordeDataClass");
	RuntimeDataClass::Serialization(Writer);

		Writer->WriteValue("Race", Race);
		Writer->WriteObjectStart("BuildingDatas");
		for (auto data : BuildingDatas)
		{
			data.Value->Serialization(Writer);
		}
		Writer->WriteObjectEnd();//BuildingDatas
	Writer->WriteObjectEnd();//HordeDataClass
}
void HordeDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	RuntimeDataClass::Deserialization(JsonObject->GetObjectField("RuntimeDataClass"));

	Race = (RaceEnum)JsonObject->GetIntegerField("Race");

	TSharedPtr<FJsonObject> jBuildingDatas = JsonObject->GetObjectField("BuildingDatas");

	for (auto jPair : jBuildingDatas->Values)
	{
		FString DataClass = jPair.Key;
		BaseBuildingDataClass * BuildingData = (BaseBuildingDataClass*)(ClassReflectManager::Get()->GetClassByName(TCHAR_TO_UTF8(*DataClass)));
		if (BuildingData)
		{
			BuildingData->Deserialization(jPair.Value->AsObject());
			BuildingDatas.Add(BuildingData->GetObjectId(), BuildingData);
		}
	}
}
BaseBuildingDataClass * HordeDataClass::SpawnBuildingData(const FString & BuildingName)
{
	FString DataClassName = FString::Printf(TEXT("%sDataClass"), *BuildingName);
	BaseBuildingDataClass * BuildingData = (BaseBuildingDataClass*)ClassReflectManager::Get()->GetClassByName(TCHAR_TO_UTF8(*DataClassName));
	BuildingData->SetConfigDataByName(BuildingName);
	BuildingData->SetParentId(GetObjectId());
	BuildingData->SetHordeBelongTo(this);
	BuildingDatas.Add(BuildingData->GetObjectId(),BuildingData);
	return BuildingData;
}
bool HordeDataClass::DestroyBuildingById(const FGuid & InId)
{
	BaseBuildingDataClass * BuildingData = GetBuildingDataById(InId);
	return DestroyBuilding(BuildingData);
}
bool HordeDataClass::DestroyBuilding(BaseBuildingDataClass * InBuildingData)
{
	bool IsOk = false;
	if (InBuildingData)
	{
		BuildingDatas.Remove(InBuildingData->GetObjectId());
		delete InBuildingData;
	}
	return MoveTemp(IsOk);
}
bool HordeDataClass::IsContains(const FGuid & InId)
{
	return GetBuildingDataById(InId) != nullptr;
}
bool HordeDataClass::IsContains(BaseBuildingDataClass * InBuildingData)
{
	return InBuildingData ? GetBuildingDataById(InBuildingData->GetObjectId()) != nullptr : false;
}
BaseBuildingDataClass * HordeDataClass::GetBuildingDataById(const FGuid & InId)
{
	if (BuildingDatas.Contains(InId))
	{
		return BuildingDatas[InId];
	}
	return nullptr;
}
int32 HordeDataClass::GetGoldNum()
{
	int32 OutNum = 0;
	TArray<MoneyStoreDataClass*> Datas = GetBuildingDatasByType<MoneyStoreDataClass>(B_MoneyStore);
	for (auto data : Datas)
	{
		OutNum += data->GetGoldNum();
	}
	return MoveTemp(OutNum);
}
int32 HordeDataClass::GetWoodNum()
{
	int32 OutNum = 0;
	TArray<WoodStoneStoreDataClass*> Datas = GetBuildingDatasByType<WoodStoneStoreDataClass>(B_WoodStoneStore);
	for (auto data : Datas)
	{
		OutNum += data->GetWoodNum();
	}
	return MoveTemp(OutNum);
}
int32 HordeDataClass::GetStoneNum()
{
	int32 OutNum = 0;
	TArray<WoodStoneStoreDataClass*> Datas = GetBuildingDatasByType<WoodStoneStoreDataClass>(B_WoodStoneStore);
	for (auto data : Datas)
	{
		OutNum += data->GetStoneNum();
	}
	return MoveTemp(OutNum);
}

