#include "HordeData.h"


void HordeData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("HordeData");
		Writer->WriteValue("HordeId", HordeId);

		Writer->WriteArrayStart("BuildingDatas");
		for (auto data : BuildingDatas)
		{
			data->Serialization(Writer);
		}
		Writer->WriteArrayEnd();//BuildingDatas
	Writer->WriteObjectEnd();//HordeData
}
void HordeData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	JsonObject->TryGetNumberField("HordeId", HordeId);
}


