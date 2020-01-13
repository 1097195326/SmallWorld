
#include "StoneStoreData.h"

G_REGISTER_CLASS(StoneStoreData)

StoneStoreData::StoneStoreData()
{
	BuildingType = B_StoneStore;
}
StoneStoreData::~StoneStoreData()
{
    
}
void StoneStoreData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("StoneStoreData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// StoneStoreData
    
}
void StoneStoreData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

