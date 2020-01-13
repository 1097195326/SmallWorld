
#include "WoodStoreData.h"

G_REGISTER_CLASS(WoodStoreData)

WoodStoreData::WoodStoreData()
{
	BuildingType = B_WoodStore;
}
WoodStoreData::~WoodStoreData()
{
    
}
void WoodStoreData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("WoodStoreData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// WoodStoreData
    
}
void WoodStoreData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

