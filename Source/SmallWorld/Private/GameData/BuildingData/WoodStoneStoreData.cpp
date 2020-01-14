
#include "WoodStoneStoreData.h"

G_REGISTER_CLASS(WoodStoneStoreData)

WoodStoneStoreData::WoodStoneStoreData()
{
	BuildingType = B_WoodStoneStore;
}
WoodStoneStoreData::~WoodStoneStoreData()
{
    
}
void WoodStoneStoreData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("WoodStoneStoreData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// WoodStoneStoreData
    
}
void WoodStoneStoreData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

