
#include "MoneyStoreData.h"

G_REGISTER_CLASS(MoneyStoreData)

MoneyStoreData::MoneyStoreData()
{
	BuildingType = B_MoneyStore;
	GoldNum = 0;
}
MoneyStoreData::~MoneyStoreData()
{
    
}
void MoneyStoreData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("MoneyStoreData");
	BaseBuildingData::Serialization(Writer);

	Writer->WriteValue("GoldNum", GoldNum);

	Writer->WriteObjectEnd();// MoneyStoreData
    
}
void MoneyStoreData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingData::Deserialization(JsonObject->GetObjectField("BaseBuildingData"));

	GoldNum = JsonObject->GetIntegerField("GoldNum");

    
}

