#include "HouseData.h"

G_REGISTER_CLASS(HouseData)

HouseData::HouseData()
{
	BuildingType = B_House;
}
HouseData::~HouseData()
{
    
}
void HouseData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("HouseData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// HouseData
    
}
void HouseData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

