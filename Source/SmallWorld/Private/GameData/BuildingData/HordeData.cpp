#include "HordeData.h"


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
int32 HordeData::GetGoldNum()
{
	int32 OutNum = 0;
	TArray<MoneyStoreData*> Datas = GetBuildingDatas<MoneyStoreData>(B_MoneyStore);
	for (auto data : Datas)
	{
		OutNum += data->GetGoldNum();
	}
	return MoveTemp(OutNum);
}
int32 HordeData::GetWoodNum()
{
	int32 OutNum = 0;
	TArray<WoodStoneStoreData*> Datas = GetBuildingDatas<WoodStoneStoreData>(B_WoodStoneStore);
	for (auto data : Datas)
	{
		OutNum += data->GetWoodNum();
	}
	return MoveTemp(OutNum);
}
int32 HordeData::GetStoneNum()
{
	int32 OutNum = 0;
	TArray<WoodStoneStoreData*> Datas = GetBuildingDatas<WoodStoneStoreData>(B_WoodStoneStore);
	for (auto data : Datas)
	{
		OutNum += data->GetStoneNum();
	}
	return MoveTemp(OutNum);
}

