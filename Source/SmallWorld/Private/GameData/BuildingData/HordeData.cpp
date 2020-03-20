#include "HordeData.h"

HordeData::~HordeData()
{
	for (auto data : BuildingDatas)
	{
		delete data;
	}
	BuildingDatas.Empty();
}
void HordeData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("HordeData");
	DataR::Serialization(Writer);

		Writer->WriteObjectStart("BuildingDatas");
		for (auto data : BuildingDatas)
		{
			data->Serialization(Writer);
		}
		Writer->WriteObjectEnd();//BuildingDatas
	Writer->WriteObjectEnd();//HordeData
}
void HordeData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	DataR::Deserialization(JsonObject->GetObjectField("DataR"));
	TSharedPtr<FJsonObject> jBuildingDatas = JsonObject->GetObjectField("BuildingDatas");

	for (auto jPair : jBuildingDatas->Values)
	{
		FString DataClass = jPair.Key;
		BaseBuildingData * BuildingData = (BaseBuildingData*)(ReflectManager::Get()->GetClassByName(TCHAR_TO_UTF8(*DataClass)));
		if (BuildingData)
		{
			BuildingData->Deserialization(jPair.Value->AsObject());
			BuildingDatas.Add(BuildingData);
		}
	}
}
BaseBuildingData * HordeData::SpawnBuilding(const FString & BuildingName)
{
	FString DataClassName = FString::Printf(TEXT("%sData"), *BuildingName);
	BaseBuildingData * BuildingData = (BaseBuildingData*)ReflectManager::Get()->GetClassByName(TCHAR_TO_UTF8(*DataClassName));
	BuildingData->SetConfigDataByName(BuildingName);
	BuildingDatas.Add(BuildingData);
	return BuildingData;
}
bool HordeData::DestroyBuildingById(const FGuid & InId)
{
	bool IsOk = false;
	BaseBuildingData * BuildingData = GetBuildingDataById(InId);
	if (BuildingData)
	{
		BuildingDatas.Remove(BuildingData);
		delete BuildingData;
	}
	return MoveTemp(IsOk);
}
bool HordeData::DestroyBuilding(BaseBuildingData * InBuildingData)
{
	bool IsOk = false;
	if (InBuildingData)
	{
		BuildingDatas.Remove(InBuildingData);
		delete InBuildingData;
	}
	return MoveTemp(IsOk);
}
BaseBuildingData * HordeData::GetBuildingDataById(const FGuid & InId)
{
	for (auto data : BuildingDatas)
	{
		if (data->GetID() ==(InId))
		{
			return data;
		}
	}
	return nullptr;
}
int32 HordeData::GetGoldNum()
{
	int32 OutNum = 0;
	TArray<MoneyStoreData*> Datas = GetBuildingDatasByType<MoneyStoreData>(B_MoneyStore);
	for (auto data : Datas)
	{
		OutNum += data->GetGoldNum();
	}
	return MoveTemp(OutNum);
}
int32 HordeData::GetWoodNum()
{
	int32 OutNum = 0;
	TArray<WoodStoneStoreData*> Datas = GetBuildingDatasByType<WoodStoneStoreData>(B_WoodStoneStore);
	for (auto data : Datas)
	{
		OutNum += data->GetWoodNum();
	}
	return MoveTemp(OutNum);
}
int32 HordeData::GetStoneNum()
{
	int32 OutNum = 0;
	TArray<WoodStoneStoreData*> Datas = GetBuildingDatasByType<WoodStoneStoreData>(B_WoodStoneStore);
	for (auto data : Datas)
	{
		OutNum += data->GetStoneNum();
	}
	return MoveTemp(OutNum);
}

