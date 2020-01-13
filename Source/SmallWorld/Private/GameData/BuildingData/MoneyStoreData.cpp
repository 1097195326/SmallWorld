
#include "MoneyStoreData.h"

G_REGISTER_CLASS(MoneyStoreData)

MoneyStoreData::MoneyStoreData()
{
	BuildingType = B_MoneyStore;
}
MoneyStoreData::~MoneyStoreData()
{
    
}
void MoneyStoreData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("MoneyStoreData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// MoneyStoreData
    
}
void MoneyStoreData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

