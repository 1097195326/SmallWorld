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


