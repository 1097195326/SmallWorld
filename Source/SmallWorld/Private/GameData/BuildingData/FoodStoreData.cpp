
#include "FoodStoreData.h"

G_REGISTER_CLASS(FoodStoreData)

FoodStoreData::FoodStoreData()
{
	BuildingType = B_FoodStore;
}
FoodStoreData::~FoodStoreData()
{
    
}
void FoodStoreData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("FoodStoreData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// FoodStoreData
    
}
void FoodStoreData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

